#include <cstdint>
#include <queue>

namespace playground{
class RateLimiter {
public:
  RateLimiter(std::int64_t timeSliceInNanos, int numEntriesAllowedPerTimeSlice);
  bool checkIfAllowed(std::int64_t currentTimestampNanos);
  void commit(std::int64_t currentTimestampNanos);
private:
  std::queue<std::int64_t> mCommittedTimestampNanos;
  std::int64_t mTimeSliceInNanos;
  int mNumEntriesAllowedPerTimeSlice;
};
}