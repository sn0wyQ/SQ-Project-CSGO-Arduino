#ifndef PC_UTILS_UTILS_H_
#define PC_UTILS_UTILS_H_

#include <iostream>

#include "Arrays/arrays.h"
#include "Global/global.h"

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

}  // namespace Utils

#endif  // PC_UTILS_UTILS_H_
