////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucket.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKET_H
#define SRC_LEAKYBUCKET_H
////////////////////////////////////////////////////////////////////////////////

#include "RateLimiter.hpp"
#include <boost/thread/mutex.hpp>
#include <queue>

#define INITIAL_LIMIT 10
#define MAX_LIMIT 100

class LeakyBucketQueue : public RateLimiter {

public:
  LeakyBucketQueue() = default;
  LeakyBucketQueue(int limit) : limit(limit) {}
  ~LeakyBucketQueue() = default;

  bool addConnection(SharedConnection) override;
  SharedConnection getConnection() override;

  // TODO: Enable dynamic limits
  // bool increaseLimit(int);
  // bool decreaseLimit(int);
  //
  // LeakyBucket &operator+(int);
  // LeakyBucket &operator-(int);

private:
  boost::mutex mtx_;
  std::queue<SharedConnection> queue;

  int limit{INITIAL_LIMIT};
  int currSize{0};
};

#endif /* SRC_LEAKYBUCKET_H */
