#ifndef PC_FEATURES_BUNNY_HOP_H_
#define PC_FEATURES_BUNNY_HOP_H_

#include "SDK/Entity/LocalPlayer/local_player.h"

#include "Arduino/arduino.h"
#include "Global/global.h"
#include "Utils/utils.h"

inline void BunnyHop(const LocalPlayer& local_player) {
  if (!Utils::IsHeld(Global::bhop_button)) {
    return;
  }

  if (local_player.IsInAir()) {
    return;
  }

  Arduino::SendCommand(CMD_JUMP);
}

#endif  // PC_FEATURES_BUNNY_HOP_H_
