////////////////////////////////////////////////////////////////////////////////
// File:        LeakyBucket.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_LEAKYBUCKET_H
#define SRC_LEAKYBUCKET_H
////////////////////////////////////////////////////////////////////////////////

#include "Connection.hpp"
#include <queue>
#include <vector>

using inner_vector = std::vector<Connection>;

class LeakyBucket {

public:
  LeakyBucket() = default;
  ~LeakyBucket() = default;

private:
  std::queue<Connection, inner_vector> queue;
};

#endif /* SRC_LEAKYBUCKET_H */
