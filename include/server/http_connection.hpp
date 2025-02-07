////////////////////////////////////////////////////////////////////////////////
// File:        server.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef INCLUDE_SERVER_HTTP_CONNECTION_H
#define INCLUDE_SERVER_HTTP_CONNECTION_H
////////////////////////////////////////////////////////////////////////////////

#include "../src/Connection.hpp"
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

namespace Server {
//------------------------------------------------------------------------------

class HttpConnection : public std::enable_shared_from_this<HttpConnection>,
                       public Connection {

public:
  HttpConnection(tcp::socket socket) : socket_(std::move(socket)) {}

  ~HttpConnection() = default;

  void start() {
    read_request();
    check_deadline();
  }

  void proceed() override;
  void abort() override;

  std::string getAddr() override {
    auto host = socket_.remote_endpoint().address().to_string();
    auto port = socket_.remote_endpoint().port();
    return host + ":" + std::to_string(port);
  }

private:
  // The socket for the currently connected client.
  tcp::socket socket_;

  // The buffer for performing reads.
  boost::beast::flat_buffer buffer_{8192};

  // The request message.
  http::request<http::dynamic_body> request_;

  // The response message.
  http::response<http::dynamic_body> response_;

  // The timer for putting a deadline on connection processing.
  boost::asio::basic_waitable_timer<std::chrono::steady_clock> deadline_{
      socket_.get_executor(), std::chrono::seconds(60)};

  // Asynchronously receive a complete request message.
  void read_request() {
    // TODO: Create a callback?
    auto self = shared_from_this();

    http::async_read(
        socket_, buffer_, request_,
        [self](boost::beast::error_code ec, std::size_t bytes_transferred) {
          boost::ignore_unused(bytes_transferred);
          if (!ec)
            self->process_request();
        });
  }

  // Determine what needs to be done with the request message.
  void process_request() {
    response_.version(request_.version());
    response_.keep_alive(false);

    switch (request_.method()) {
    case http::verb::get:
      response_.result(http::status::ok);
      response_.set(http::field::server, "Beast");
      create_response();
      break;

    default:
      // We return responses indicating an error if
      // we do not recognize the request method.
      response_.result(http::status::bad_request);
      response_.set(http::field::content_type, "text/plain");
      boost::beast::ostream(response_.body())
          << "Invalid request-method '" << request_.method_string() << "'";
      break;
    }

    write_response();
  }

  // Construct a response message based on the program state.
  void create_response() {
    if (request_.target() == "/hello") {
      response_.set(http::field::content_type, "text/html");
      boost::beast::ostream(response_.body())
          << "<html>\n"
          << "<head><title>Beast Hello World</title></head>\n"
          << "<body>\n"
          << "<h1>Hello World</h1>\n"
          << "<p>Hello World from C++ (Beast)</p>\n"
          << "</body>\n"
          << "</html>\n";
    } else if (request_.target() == "/time") {
      response_.set(http::field::content_type, "text/html");
      boost::beast::ostream(response_.body())
          << "<html>\n"
          << "<head><title>Current time</title></head>\n"
          << "<body>\n"
          << "<h1>Current time</h1>\n"
          << "<p>The current time is " << std::time(0)
          << " seconds since the epoch.</p>\n"
          << "</body>\n"
          << "</html>\n";
    } else {
      response_.result(http::status::not_found);
      response_.set(http::field::content_type, "text/plain");
      boost::beast::ostream(response_.body()) << "File not found\r\n";
    }
  }

  // Asynchronously transmit the response message.
  void write_response() {
    auto self = shared_from_this();

    response_.set(http::field::content_length,
                  std::to_string(response_.body().size()));

    http::async_write(socket_, response_,
                      [self](boost::beast::error_code ec, std::size_t) {
                        self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                        self->deadline_.cancel();
                      });
  }

  // Check whether we have spent enough time on this connection.
  void check_deadline() {
    auto self = shared_from_this();

    deadline_.async_wait([self](boost::beast::error_code ec) {
      if (!ec) {
        // Close socket to cancel any outstanding operation.
        self->socket_.close(ec);
      }
    });
  }
};

//------------------------------------------------------------------------------

} // namespace Server
#endif /* INCLUDE_SERVER_HTTP_CONNECTION_H  */
