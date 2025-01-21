#include "LeakyBucket.hpp"
#include <cstddef>
#include <memory>

bool LeakyBucket::addConnection(SharedConnection conn) {
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

SharedConnection LeakyBucket::getConnection() {
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
