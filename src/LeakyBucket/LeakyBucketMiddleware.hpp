////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucketTimer.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKETTIMER_H
#define SRC_LEAKYBUCKETTIMER_H
////////////////////////////////////////////////////////////////////////////////

#include "../Middleware.hpp"
#include "LeakyBucketQueue.hpp"

// TODO: Join with Queue, so it its only one
class LeakyBucketMiddleware : public Middleware {

public:
  LeakyBucketMiddleware() {};
  LeakyBucketMiddleware(int limit) : queue(LeakyBucketQueue(limit)) {};

  ~LeakyBucketMiddleware() = default;

  void addConnection(SharedConnection) override;

  void tick() override;

private:
  LeakyBucketQueue queue{};
};

#endif /* SRC_LEAKYBUCKETTIMER_H */
