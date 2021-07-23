#ifndef PC_SDK_ENTITY_LOCALPLAYER_LOCAL_PLAYER_H_
#define PC_SDK_ENTITY_LOCALPLAYER_LOCAL_PLAYER_H_

#include <utility>

#include "SDK/Entity/entity.h"
#include "SDK/Entity/LocalPlayer/abstract_local_player.h"
#include "SDK/EntityList/entity_list.h"

#include "Memory/memory.h"
#include "Utils/utils.h"
#include "Vector/vector.h"
#include "dump.h"

class LocalPlayer : public AbstractLocalPlayer {
 public:
  LocalPlayer(const Module& client, const DWORD client_state);

  int GetCrosshairId() const;

  Vector GetLocalViewAngle() const;

  std::pair<Vector, float> GetAimAngleDiffAndDistance(
      const EntityList& entity_list, int bone, float max_fov) const;

  Vector GetAngleToTarget(const Entity& target, int bone) const;

  float GetSensitivity() const override;

 private:
  DWORD client_address_{0};
  DWORD client_state_{0};
};

#endif  // PC_SDK_ENTITY_LOCALPLAYER_LOCAL_PLAYER_H_
