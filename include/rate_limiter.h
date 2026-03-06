#include <cstdint>

namespace playground{
class RateLimiter {
public:
  RateLimiter(std::int64_t timeInNanos, int numEntriesAllowedPerTimeSlice);
  bool checkIfAllowed(std::int64_t currentTimestampNanos);
  void commit(std::int64_t currentTimestampNanos);
};
}