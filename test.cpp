#include "include/rate_limiter.h"
#include <iostream>

template <typename T>
void EXPECT_EQ(T expected, T actual) {
  if (expected != actual) {
    std::cout << "FAILED! expected: " << expected << ", but got: " << actual << std::endl;
  }
}

void test_max_4_request_per_nanos() {
  std::cout << "===== Running test_max_4_request_per_nanos =====" << std::endl;
  playground::RateLimiter victim {1, 4};
  std::int64_t ts {1};
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  EXPECT_EQ(victim.checkIfAllowed(ts), false);
  std::cout << "===== Finished test_max_4_request_per_nanos =====" << std::endl;
}


void test_max_2_request_per_second() {
  std::cout << "===== Running test_max_2_request_per_second =====" << std::endl;

  playground::RateLimiter victim {static_cast<std::int64_t>(1e9), 2};
  std::int64_t ts {1};
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  ts += 10;
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  ts +=100;
  EXPECT_EQ(victim.checkIfAllowed(ts), false);
  std::cout << "===== Finished test_max_2_request_per_second =====" << std::endl;

}

void test_max_2_request_per_second_window_slides() {
  std::cout << "===== Running test_max_2_request_per_second_window_slides =====" << std::endl;

  playground::RateLimiter victim {static_cast<std::int64_t>(1e9), 4};
  std::int64_t ts {1};
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  ts += 10;
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  ts += static_cast<std::int64_t>(1e9);
  EXPECT_EQ(victim.checkIfAllowed(ts), true);
  victim.commit(ts);
  std::cout << "===== Finished test_max_2_request_per_second_window_slides =====" << std::endl;

}

int main() {
  test_max_4_request_per_nanos();
  test_max_2_request_per_second();
  test_max_2_request_per_second_window_slides();

  return 0;
}
