#ifndef ARDUINO_HELPERS_BYTES_H_
#define ARDUINO_HELPERS_BYTES_H_

#include <Arduino.h>

namespace Bytes {

byte kWall[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

byte kHeart[8] = {
    B00000,
    B00000,
    B01010,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000
};

}  // namespace Bytes

#endif  // ARDUINO_HELPERS_BYTES_H_
