////////////////////////////////////////////////////////////////////////////////
// File:        SlidingWindowMiddleware.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_SLIDINGWINDOWMIDDLEWARE_H
#define SRC_SLIDINGWINDOWMIDDLEWARE_H
////////////////////////////////////////////////////////////////////////////////

#include "Middleware.hpp"
class SlidingWindowMiddleware : public Middleware {

public:
  SlidingWindowMiddleware() = default;
  ~SlidingWindowMiddleware() = default;

  void addConnection(SharedConnection) override;
  void tick() override;

private:
};

#endif /* SRC_SLIDINGWINDOWMIDDLEWARE_H */
