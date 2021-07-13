#include "timer.h"

Timer::Timer() : start_time_(std::chrono::steady_clock::now()) {}

int Timer::GetElapsedMs() const {
  return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - start_time_).count());
}

float Timer::GetElapsedS() const {
  return static_cast<float>(GetElapsedMs()) / 1000.f;
}
