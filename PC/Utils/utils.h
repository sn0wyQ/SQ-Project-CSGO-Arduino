#ifndef PC_UTILS_UTILS_H_
#define PC_UTILS_UTILS_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

#include "SDK/Entity/LocalPlayer/abstract_local_player.h"

#include "Arrays/arrays.h"
#include "Global/global.h"
#include "Memory/memory.h"
#include "Vector/vector.h"
#include "dump.h"

namespace Utils {

void Log(const char* format);
template<class T, class ...Ts>
void Log(const char* format, const T& current_arg, const Ts&... args) {
  while (*format != '\0') {
    if (*format == '%') {
      std::cout << current_arg;
      Log(format + 1, args...);
      return;
    }
    std::cout << *format;
    ++format;
  }
}

void GetKey(int* final_key_code, const char* purpose);

bool IsHeld(int key_code);

std::pair<char, char> AngleDiffToMouseDelta(
    const AbstractLocalPlayer& local_player,
    const Vector& angle,
    float distance);

}  // namespace Utils

#endif  // PC_UTILS_UTILS_H_
