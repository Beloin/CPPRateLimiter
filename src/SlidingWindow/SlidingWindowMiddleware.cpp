#include "SlidingWindowMiddleware.hpp"
#include <iostream>

time_point get_now() { return std::chrono::system_clock::now(); }

void SlidingWindowMiddleware::addConnection(SharedConnection connection) {
  removeOutdated();
  if (requestsQueue.size() + 1 > requestPerPeriod) {
    connection->abort();
    return;
  }

  auto addr = connection->getAddr();
  connection->proceed();
  requestsQueue.emplace(get_now(), addr);
}

void SlidingWindowMiddleware::removeOutdated() {
  auto now = get_now();
  auto req = requestsQueue.front();
  auto time = std::get<0>(req);
  auto addr = std::get<1>(req);
  auto between = std::chrono::duration<double, std::milli>(now - time);
  while (between.count() > msPeriod || requestsQueue.empty()) {
    std::cout << "Popping request from addr " << addr << std::endl;;
    requestsQueue.pop();
    req = requestsQueue.front();
    time = std::get<0>(req);
    addr = std::get<1>(req);
    between = std::chrono::duration<double, std::milli>(now - time);
  }
}

void SlidingWindowMiddleware::tick() {
  // No-op
}
