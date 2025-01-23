////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucketTimer.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKETTIMER_H
#define SRC_LEAKYBUCKETTIMER_H
////////////////////////////////////////////////////////////////////////////////

#include "LeakyBucketQueue.hpp"
#include "../Middleware.hpp"

// TODO: Join with Queue, so it its only one
class LeakyBucketMiddleware : public Middleware {

public:
  LeakyBucketMiddleware() {};
  LeakyBucketMiddleware(int ms, int limit)
      : ms_timer(ms), queue(LeakyBucketQueue(limit)) {};

  ~LeakyBucketMiddleware() = default;

  void addConnection(SharedConnection) override;

  void tick() override;

private:
  LeakyBucketQueue queue{};
  int ms_timer{100};
};

#endif /* SRC_LEAKYBUCKETTIMER_H */
