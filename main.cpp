#include "server/http_connection.hpp"
#include "src/LeakyBucketMiddleware.hpp"
#include <boost/asio/ip/address.hpp>
#include <boost/beast.hpp>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

using tcp = boost::asio::ip::tcp;
int runserver(int argc, char **argv);
void http_server(tcp::acceptor &acceptor, tcp::socket &socket,
                 LeakyBucketMiddleware &middleware);

int main(int argc, char *argv[]) {
  std::cout << "[server] Starting Server" << std::endl;
  return runserver(argc, argv);
}

void timer_tick(boost::asio::steady_timer &timer, boost::asio::io_context &io,
                std::chrono::milliseconds interval,
                LeakyBucketMiddleware &middleware) {
  middleware.tick();

  timer.expires_after(interval);
  timer.async_wait([&timer, &io, interval,
                    &middleware](const boost::system::error_code &ec) {
    if (!ec) {
      timer_tick(timer, io, interval, middleware);
    } else if (ec != boost::asio::error::operation_aborted) {
      std::cerr << "Timer error: " << ec.message() << '\n';
    }
  });
}

int runserver(int argc, char **argv) {
  LeakyBucketMiddleware middleware{};
  try {
    // Check command line arguments.
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80\n";
      return EXIT_FAILURE;
    }

    auto const address = boost::asio::ip::make_address(argv[1]);
    unsigned short port = static_cast<unsigned short>(std::atoi(argv[2]));

    boost::asio::io_context ioc{};

    tcp::acceptor acceptor{ioc, {address, port}};
    tcp::socket socket{ioc};
    http_server(acceptor, socket, middleware);

    std::chrono::milliseconds interval(100); // 0.1 sec
    boost::asio::steady_timer timer(ioc, interval);
    timer.async_wait([&timer, &ioc, interval,
                      &middleware](const boost::system::error_code &ec) {
      if (!ec) {
        timer_tick(timer, ioc, interval, middleware);
      } else {
        std::cerr << "Initial timer error: " << ec.message() << '\n';
      }
    });

    ioc.run();
    return 0;
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}

void http_server(tcp::acceptor &acceptor, tcp::socket &socket,
                 LeakyBucketMiddleware &middleware) {
  acceptor.async_accept(socket, [&](boost::beast::error_code ec) {
    if (!ec) {
      auto sharedConnection =
          std::make_shared<Server::HttpConnection>(std::move(socket));
      middleware.addConnection(sharedConnection);
      // sharedConnection->start();
    }
    http_server(acceptor, socket, middleware);
  });
}
