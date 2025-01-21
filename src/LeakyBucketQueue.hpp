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
#include <vector>

#define INITIAL_LIMIT 10
#define MAX_LIMIT 100

using inner_vector = std::vector<SharedConnection>;
class LeakyBucketQueue : public RateLimiter {

public:
  LeakyBucketQueue() = default;
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
  int limit{INITIAL_LIMIT};
  int currSize{0};

  std::queue<SharedConnection, inner_vector> queue;
};

#endif /* SRC_LEAKYBUCKET_H */
