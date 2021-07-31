#include "utils.h"

void Utils::Log(const char* format) {
  std::cout << format << std::endl;
}

void Utils::GetKey(int* final_key_code, const char* purpose) {
  while (!(*final_key_code)) {
    std::cout << "Enter key code for " << purpose << ": ";
    int key_code;
    std::cin >> key_code;
    if (Arrays::kKeyNames.find(key_code) == Arrays::kKeyNames.end()) {
      Utils::Log("Can NOT associate entered key code with any key!");
    } else {
      Utils::Log("Selected key is %", Arrays::kKeyNames.at(key_code));
      std::cout << "OK? (y/n): ";
      char answer;
      std::cin >> answer;
      if (answer == 'y' || answer == 'Y') {
        *final_key_code = key_code;
      }
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

std::pair<char, char> Utils::AngleDiffToMouseDelta(
    const AbstractLocalPlayer& local_player,
    const Vector& angle,
    float distance) {
  float delta_x = -std::sin(DegToRad(angle.y)) * distance;
  float delta_y = std::sin(DegToRad(angle.x)) * distance;

  float crosshair_dist = std::sqrt((delta_x * delta_x) + (delta_y * delta_y));
  // If crosshair_dist is small than we need more precision in mouse movement
  // => we make mouse move slower when crosshair comes closer to target
  float speed = (crosshair_dist < 30.f ? 5.f : 15.f);
  // And even more precision if we are far from target
  if (distance > 1024.f) {
    speed *= 0.25f;
  } else if (distance > 512.f) {
    speed *= 0.5f;
  } else if (distance > 256.f) {
    speed *= 0.75f;
  }

  float sensitivity = local_player.GetSensitivity();
  float coef = speed / sensitivity;
  delta_x *= coef;
  delta_y *= coef;

  return std::make_pair(ClampFloatToChar(delta_x), ClampFloatToChar(delta_y));
}
