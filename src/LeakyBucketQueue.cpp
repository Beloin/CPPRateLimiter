#include "LeakyBucketQueue.hpp"
#include <cstddef>
#include <memory>

bool LeakyBucketQueue::addConnection(SharedConnection conn) {
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

SharedConnection LeakyBucketQueue::getConnection() {
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
