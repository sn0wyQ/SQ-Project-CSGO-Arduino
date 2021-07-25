#ifndef ARDUINO_HELPERS_ARRAYS_H_
#define ARDUINO_HELPERS_ARRAYS_H_

#include <Arduino.h>

namespace Arrays {

const String kState[] {
    "Off",
    "On",
};

const String kBhopBtns[] {
  "Off",
  "Space",
  "MwhUp",
};

const String kBoneNames[] {
  "Stomach",
  "Chest",
  "Neck",
  "Head",
};

}  // namespace Arrays

#endif  // ARDUINO_HELPERS_ARRAYS_H_
