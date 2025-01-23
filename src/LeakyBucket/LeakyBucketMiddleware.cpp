#include "LeakyBucketMiddleware.hpp"
#include <iostream>

// TODO: Check ms
void LeakyBucketMiddleware::tick() {
  auto conn = queue.getConnection();
  if (conn == nullptr) {
    return;
  }

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
