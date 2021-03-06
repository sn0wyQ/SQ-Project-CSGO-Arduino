#ifndef PC_GLOBAL_GLOBAL_H_
#define PC_GLOBAL_GLOBAL_H_

#include <vector>

namespace Global {

// Buttons
extern int bhop_button;
extern int trigger_bot_button;
extern int aim_bot_button;

// Settings
extern int aim_bot_bone;
extern float aim_bot_fov;
extern float aim_bot_smooth;

// Window size
extern float window_w;
extern float window_h;

// Aim bones
extern const std::vector<int> kBones;

}  // namespace Global

#endif  // PC_GLOBAL_GLOBAL_H_
