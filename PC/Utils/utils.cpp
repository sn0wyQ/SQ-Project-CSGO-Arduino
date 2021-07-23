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

char ClampFloatToChar(float x) {
  if (x < -126.9f) {
    return -127;
  }

  if (x > 126.9f) {
    return 127;
  }

  return static_cast<char>(x);
}

std::pair<char, char>
    Utils::AngleDiffToMouseDelta(const AbstractLocalPlayer& local_player,
                                 const Vector& angle,
                                 float distance) {
  float sensitivity = local_player.GetSensitivity();
  // We multiply by 10.f so aim is NOT so slow
  float coef = (distance * 10.f) / sensitivity;

  float delta_x = ClampFloatToChar(-std::sin(DEG2RAD(angle.y)) * coef);
  float delta_y = ClampFloatToChar(std::sin(DEG2RAD(angle.x)) * coef);

  return std::make_pair(static_cast<char>(delta_x), static_cast<char>(delta_y));
}
