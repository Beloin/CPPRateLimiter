#include "LeakyBucketMiddleware.hpp"
#include <iostream>

// TODO: Check ms
void LeakyBucketMiddleware::tick() {
  auto conn = getConnection();
  if (conn == nullptr) {
    return;
  }

  conn->proceed();
}

void LeakyBucketMiddleware::addConnection(SharedConnection conn) {
  bool accepted = addConnectionToQueue(conn);
  if (!accepted) {
    conn->abort();
    std::cout << "(middleware) Aborted Connection " << conn->getAddr()
              << std::endl;
    return;
  }

  std::cout << "(middleware) Added Connection " << conn->getAddr()
            << std::endl;
}


bool LeakyBucketMiddleware::addConnectionToQueue(SharedConnection conn) {
  mtx_.lock();
  if (currSize + 1 > limit) {
    mtx_.unlock();
    return false;
  }

  queue.push(conn);
  currSize++;
  mtx_.unlock();

  return true;
}

SharedConnection LeakyBucketMiddleware::getConnection() {
  mtx_.lock();
  if (currSize == 0) {
    mtx_.unlock();
    return std::nullptr_t{};
  }

  auto conn = queue.front();
  queue.pop();
  currSize--;
  mtx_.unlock();

  return conn;
}

