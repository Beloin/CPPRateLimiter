////////////////////////////////////////////////////////////////////////////////
// File:        Ratelimiter.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_RATELIMITER_H
#define SRC_RATELIMITER_H
////////////////////////////////////////////////////////////////////////////////

#include "Connection.hpp"
#include <memory>

using SharedConnection = std::shared_ptr<Connection>;

class RateLimiter {

public:
  virtual bool addConnection(SharedConnection) = 0;
  virtual SharedConnection getConnection() = 0;
};

#endif /* SRC_RATELIMITER_H */
