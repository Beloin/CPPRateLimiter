#include "LeakyBucketMiddleware.hpp"
#include <iostream>

void LeakyBucketMiddleware::tick() {
  std::cout << "(middleware) Running middleware" << std::endl;
  // TODO: Check ms
  auto conn = queue.getConnection();
  if (conn == nullptr) {
    return;
  }

  // TODO: Test aborting all requests
  // conn->abort();
  conn->proceed();
}

void LeakyBucketMiddleware::addConnection(SharedConnection conn) {
  bool accepted = queue.addConnection(conn);
  if (!accepted) {
    conn->abort();
    std::cout << "(middleware) Aborted Connection " << conn->getAddr()
              << std::endl;
    return;
  }

  std::cout << "(middleware) Added Connection " << conn->getAddr()
            << std::endl;
}
