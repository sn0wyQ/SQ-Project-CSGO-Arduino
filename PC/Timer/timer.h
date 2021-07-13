#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

class Timer : public std::chrono::high_resolution_clock {
 public:
  Timer();

  int GetElapsedMs() const;
  float GetElapsedS() const;

 private:
  const std::chrono::time_point<std::chrono::steady_clock> start_time_;
};

#endif  // TIMER_H_
