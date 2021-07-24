#ifndef PC_FEATURES_TRIGGER_BOT_H_
#define PC_FEATURES_TRIGGER_BOT_H_

#include "SDK/Entity/LocalPlayer/local_player.h"
#include "SDK/Entity/entity.h"
#include "SDK/EntityList/entity_list.h"

#include "Arduino/arduino.h"
#include "Global/global.h"
#include "Utils/utils.h"

inline void TriggerBot(const LocalPlayer& local_player,
                       const EntityList& entity_list) {
  if (!Utils::IsHeld(Global::trigger_bot_button)) {
    return;
  }

  int target_entity_id = local_player.GetCrosshairId();
  if (!EntityList::CanBeEntity(target_entity_id)) {
    return;
  }

  Entity target_entity = entity_list.GetEntity(target_entity_id);
  if (!target_entity.IsAlive()
      || target_entity.GetTeam() == local_player.GetTeam()) {
    return;
  }

  Arduino::SendCommand(CMD_SHOOT);
}

#endif  // PC_FEATURES_TRIGGER_BOT_H_
