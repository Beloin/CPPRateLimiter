#include "LeakyBucketTimer.hpp"
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>

using namespace boost;
using Timer = shared_ptr<asio::deadline_timer>;

void LeakyBucketTimer::run(int milli) {}
