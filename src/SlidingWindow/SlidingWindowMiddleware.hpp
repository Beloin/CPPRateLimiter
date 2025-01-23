////////////////////////////////////////////////////////////////////////////////
// File:        SlidingWindowMiddleware.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_SLIDINGWINDOWMIDDLEWARE_H
#define SRC_SLIDINGWINDOWMIDDLEWARE_H
////////////////////////////////////////////////////////////////////////////////

#include "../Middleware.hpp"
#include <stack>

class SlidingWindowMiddleware : public Middleware {

public:
  SlidingWindowMiddleware() = default;
  ~SlidingWindowMiddleware() = default;

  void addConnection(SharedConnection) override;
  void tick() override;

private:
  int requestPerSec{5};
  // TODO: Add object in stack or something like this
  std::stack<SharedConnection> stack;
};

#endif /* SRC_SLIDINGWINDOWMIDDLEWARE_H */
