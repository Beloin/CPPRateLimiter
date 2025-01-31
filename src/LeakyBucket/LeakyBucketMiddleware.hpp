////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucketTimer.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKETTIMER_H
#define SRC_LEAKYBUCKETTIMER_H
////////////////////////////////////////////////////////////////////////////////

#include "../Middleware.hpp"
#include <boost/thread/pthread/mutex.hpp>
#include <queue>

#define INITIAL_LIMIT 10
#define MAX_LIMIT 100

class LeakyBucketMiddleware : public Middleware {

public:
  LeakyBucketMiddleware() {};
  LeakyBucketMiddleware(int limit) : limit(limit) {};

  ~LeakyBucketMiddleware() = default;

  void addConnection(SharedConnection) override;

  void tick() override;

private:
  SharedConnection getConnection();
  bool addConnectionToQueue(SharedConnection);

  boost::mutex mtx_;
  std::queue<SharedConnection> queue;

  int limit{INITIAL_LIMIT};
  int currSize{0};
};

#endif /* SRC_LEAKYBUCKETTIMER_H */
