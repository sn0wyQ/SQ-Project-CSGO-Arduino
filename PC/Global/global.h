#ifndef PC_GLOBAL_GLOBAL_H_
#define PC_GLOBAL_GLOBAL_H_

#include <cstdint>

#include "Arduino/arduino.h"

namespace Global {

// Buttons
extern int bhop_button;
extern int trigger_bot_button;
extern int aim_bot_button;

// Window size
extern float window_w;
extern float window_h;

}  // namespace Global

#endif  // PC_GLOBAL_GLOBAL_H_
