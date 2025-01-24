////////////////////////////////////////////////////////////////////////////////
// File:        SlidingWindowMiddleware.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_SLIDINGWINDOWMIDDLEWARE_H
#define SRC_SLIDINGWINDOWMIDDLEWARE_H
////////////////////////////////////////////////////////////////////////////////

#include "../Middleware.hpp"
#include <chrono>
#include <ctime>
#include <queue>

using time_point = std::chrono::system_clock::time_point;

typedef std::tuple<time_point, std::string> TimedInfo;

class SlidingWindowMiddleware : public Middleware {

public:
  SlidingWindowMiddleware() = default;
  SlidingWindowMiddleware(int reqPerPeriod, int period)
      : requestPerPeriod(reqPerPeriod), msPeriod(period) {}

  ~SlidingWindowMiddleware() = default;

  void addConnection(SharedConnection) override;
  void tick() override;

private:
  int requestPerPeriod{5};
  int msPeriod{100};

  std::queue<TimedInfo> requestsQueue;

  void removeOutdated();
};

#endif /* SRC_SLIDINGWINDOWMIDDLEWARE_H */
