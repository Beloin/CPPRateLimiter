////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucketTimer.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKETTIMER_H
#define SRC_LEAKYBUCKETTIMER_H
////////////////////////////////////////////////////////////////////////////////

#include "LeakyBucketQueue.hpp"

class LeakyBucketMiddleware {

public:
  LeakyBucketMiddleware(){
  };
  ~LeakyBucketMiddleware() = default;

  void setup(int ms);
  void addConnection(SharedConnection);

  // TODO: Maybe focus only in the thing to do, not in the timer
  // So we can create the timer in the main class
  // void run();
  // TODO: Or implement the "RateLimiter" here and make the timer in run,
  // Implement the RateLimiter and add the timer, so everytime we add a thing
  // here we can wait only for the timer. Actually the LeakyBucketQueue can be
  // the DefaultRateLimiter, but with a timer Or we can remplement the
  // RateLimiter here and add the timer as background job, respecting an setup
  // function
  // Or just a tick function that uses the dictated time
  // Should be ticked in $setup time
  // Create a tick time configuration? So the timer is inside the tick?
  void tick();

private:
  LeakyBucketQueue queue{};
};

#endif /* SRC_LEAKYBUCKETTIMER_H */
