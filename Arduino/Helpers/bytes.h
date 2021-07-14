#ifndef ARDUINO_HELPERS_BYTES_H_
#define ARDUINO_HELPERS_BYTES_H_

#include <Arduino.h>

namespace Bytes {

byte kC4[] = {
    B01111,
    B10000,
    B10000,
    B10101,
    B10111,
    B10001,
    B10000,
    B01111
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

byte kKit[] = {
    B01010,
    B01010,
    B00100,
    B01010,
    B10001,
    B10001,
    B10001,
    B01010
};

byte kLockClosed[] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B11111,
    B11111,
    B11111,
    B11111
};

byte kLockOpened[] = {
    B01110,
    B10001,
    B00001,
    B00001,
    B11111,
    B11111,
    B11111,
    B11111
};

byte kVest[] = {
    B01110,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B01010,
    B00100
};

byte kVestHelm[] = {
    B01110,
    B10001,
    B11111,
    B11011,
    B10001,
    B10001,
    B01010,
    B00100
};

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

}  // namespace Bytes

#endif  // ARDUINO_HELPERS_BYTES_H_
