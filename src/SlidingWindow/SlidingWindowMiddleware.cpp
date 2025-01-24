#include "SlidingWindowMiddleware.hpp"
#include <iostream>

time_point get_now() { return std::chrono::system_clock::now(); }

void SlidingWindowMiddleware::addConnection(SharedConnection connection) {
  mut.lock();
  removeOutdated();
  if (requestsQueue.size() + 1 > requestPerPeriod) {
    mut.unlock();
    connection->abort();
    return;
  }

  auto addr = connection->getAddr();
  requestsQueue.emplace(get_now(), addr);
  mut.unlock();

  connection->proceed();
}

void SlidingWindowMiddleware::removeOutdated() {
  if (requestsQueue.empty())
    return;
  auto now = get_now();
  auto req = requestsQueue.front();
  auto time = std::get<0>(req);
  auto addr = std::get<1>(req);
  auto between = std::chrono::duration<double, std::milli>(now - time);
  while (between.count() > msPeriod || requestsQueue.empty()) {
    std::cout << "Popping request from addr " << addr << std::endl;
    requestsQueue.pop();

    if (requestsQueue.empty())
      break;

    req = requestsQueue.front();
    time = std::get<0>(req);
    addr = std::get<1>(req);
    between = std::chrono::duration<double, std::milli>(now - time);
  }
}

void SlidingWindowMiddleware::tick() {
  // No-op
}
