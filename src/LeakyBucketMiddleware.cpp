#include "LeakyBucketMiddleware.hpp"

void LeakyBucketMiddleware::tick() {
  // TODO: Check ms
  auto conn = queue.getConnection();
  if (conn == nullptr) {
    return;
  }

  // TODO: Test aborting all requests
  conn->abort();
  // conn->proceed();
}

void LeakyBucketMiddleware::addConnection(SharedConnection conn) {
  bool accepted = queue.addConnection(conn);
  if (!accepted) {
    conn->abort();
  }
}
