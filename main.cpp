#include "server/http_connection.hpp"
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
void http_server(tcp::acceptor &acceptor, tcp::socket &socket);

int main(int argc, char *argv[]) {
  std::cout << "Hello World" << std::endl;
  return runserver(argc, argv);
}

int runserver(int argc, char **argv) {
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

    boost::asio::io_context ioc{1};

    tcp::acceptor acceptor{ioc, {address, port}};
    tcp::socket socket{ioc};
    http_server(acceptor, socket);

    ioc.run();
    return 0;
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}

void http_server(tcp::acceptor &acceptor, tcp::socket &socket) {
  acceptor.async_accept(socket, [&](boost::beast::error_code ec) {
    if (!ec)
      std::make_shared<Server::HttpConnection>(std::move(socket))->start();
    http_server(acceptor, socket);
  });
}
