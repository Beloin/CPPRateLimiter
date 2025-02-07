#include "server/http_connection.hpp"
#include <iostream>

void Server::HttpConnection::proceed() {
  start();
}

void Server::HttpConnection::abort() {
  response_.result(http::status::too_many_requests);
  response_.set(http::field::content_type, "text/plain");
  boost::beast::ostream(response_.body()) << "Server overheat" << std::endl;
  // Async writes
  write_response();
  check_deadline();
}
