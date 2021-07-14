#include "utils.h"

void Utils::Log(const char* format) {
  std::cout << format << std::endl;
}

void Utils::GetKey(int* final_key_code, const char* purpose) {
  while (!(*final_key_code)) {
    std::cout << "Enter key code for " << purpose << ": ";
    int key_code;
    std::cin >> key_code;
    Utils::Log("Selected key is %", Arrays::kKeyNames.at(key_code));
    std::cout << "OK? (y/n): ";
    char answer;
    std::cin >> answer;
    if (answer == 'y' || answer == 'Y') {
      *final_key_code = key_code;
    }
    std::cout << std::endl;
  }
}

bool Utils::IsHeld(int key_code) {
  return (GetAsyncKeyState(key_code) & 0x8000);
}
