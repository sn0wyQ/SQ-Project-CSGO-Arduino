#ifndef PC_FEATURES_AIM_BOT_H_
#define PC_FEATURES_AIM_BOT_H_

#include <utility>

#include "SDK/Entity/LocalPlayer/local_player.h"
#include "SDK/EntityList/entity_list.h"

#include "Arduino/arduino.h"
#include "Global/global.h"
#include "Utils/utils.h"
#include "Vector/vector.h"

inline void AimBot(const LocalPlayer& local_player,
                   const EntityList& entity_list) {
  if (!Utils::IsHeld(Global::aim_bot_button)) {
    return;
  }

  std::pair<Vector, float> angle_diff_and_distance =
      local_player.GetAimAngleDiffAndDistance(entity_list, 8, 180.f);
  Vector angle_diff = angle_diff_and_distance.first;
  float distance = angle_diff_and_distance.second;

  std::pair<char, char> mouse_delta =
      Utils::AngleDiffToMouseDelta(local_player, angle_diff, distance);
  Arduino::SendCommand(CMD_AIM, {mouse_delta.first, mouse_delta.second});
}

#endif  // PC_FEATURES_AIM_BOT_H_
