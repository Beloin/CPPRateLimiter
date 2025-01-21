////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucket.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKET_H
#define SRC_LEAKYBUCKET_H
////////////////////////////////////////////////////////////////////////////////

#include "Connection.hpp"
#include <memory>
#include <queue>
#include <vector>
#include <boost/thread/mutex.hpp>


#define INITIAL_LIMIT 10
#define MAX_LIMIT 100

using SharedConnection = std::shared_ptr<Connection>;
using inner_vector = std::vector<SharedConnection>;
class LeakyBucket {

public:
  LeakyBucket() = default;
  ~LeakyBucket() = default;

  bool addConnection(SharedConnection);
  SharedConnection getConnection();

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
