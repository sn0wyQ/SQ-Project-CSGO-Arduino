#include "global.h"

// Buttons
int Global::bhop_button = 0;
int Global::trigger_bot_button = 0;
int Global::aim_bot_button = 0;

// Settings
int Global::aim_bot_bone = 8;  // Head by default

// Window size
float Global::window_w = 1280;
float Global::window_h = 720;

// Aim bones
const std::vector<int> Global::kBones = {
    3,  // Stomach
    6,  // Chest
    7,  // Neck
    8,  // Head
};
