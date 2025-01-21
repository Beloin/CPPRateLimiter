////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucketTimer.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKETTIMER_H
#define SRC_LEAKYBUCKETTIMER_H
////////////////////////////////////////////////////////////////////////////////

#include "RateLimiter.hpp"
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/detail/error_code.hpp>
class LeakyBucketTimer {

public:
  LeakyBucketTimer() {

  };
  ~LeakyBucketTimer() = default;

  // TODO: Maybe focus only in the thing to do, not in the timer
  // So we can create the timer in the main class
  void run();
  void addConnection(SharedConnection);
  // TODO: Or implement the "RateLimiter" here and make the timer in run, 
  // Implement the RateLimiter and add the timer, so everytime we add a thing here 
  // we can wait only for the timer. Actually the LeakyBucketQueue can be the DefaultRateLimiter, but with a timer
  // Or we can remplement the RateLimiter here and add the timer as background job, respecting an setup
  // function 

private:
};

#endif /* SRC_LEAKYBUCKETTIMER_H */
