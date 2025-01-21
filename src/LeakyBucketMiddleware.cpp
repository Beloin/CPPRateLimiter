#include "LeakyBucketMiddleware.hpp"
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/make_shared.hpp>
// #include <cstddef>
// #include <functional>
//
// using namespace boost;
// using Timer = shared_ptr<asio::deadline_timer>;

// void LeakyBucketTimer::setup(int milli, boost::asio::io_context ctx) {
//   boost::posix_time::millisec ms{milli};
//   timer = boost::asio::deadline_timer{ctx, ms};
//
//   // Reschedule the timer for 1 second in the future:
//   timer.expires_at(timer.expires_at() + ms);
//   // Posts the timer event
//   timer.async_wait(bind(tick, asio::placeholders::error));
// }
//
// void LeakyBucketTimer::tick(const boost::system::error_code &) {
//   // Reschedule the timer for 1 second in the future:
//   timer.expires_at(timer.expires_at() + ms);
//   // Posts the timer event
//   timer.async_wait(tick);
// }

void LeakyBucketMiddleware::setup(int ms) {
  // No-op
}

void LeakyBucketMiddleware::tick() {
  // TODO: Check ms
  auto conn = queue.getConnection();
  if (conn == nullptr) {
    return;
  }
  conn->proceed();
}

void LeakyBucketMiddleware::addConnection(SharedConnection conn) {
  bool accepted = queue.addConnection(conn);
  if (!accepted) {
    conn->abort();
  }
}
