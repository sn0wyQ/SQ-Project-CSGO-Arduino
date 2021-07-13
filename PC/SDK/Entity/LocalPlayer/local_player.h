#ifndef PC_SDK_ENTITY_LOCALPLAYER_LOCAL_PLAYER_H_
#define PC_SDK_ENTITY_LOCALPLAYER_LOCAL_PLAYER_H_

#include "SDK/Entity/entity.h"

#include "Memory/memory.h"
#include "dump.h"

class LocalPlayer : public Entity {
 public:
  explicit LocalPlayer(const Module& client);

  int GetCrosshairId() const;
};

#endif  // PC_SDK_ENTITY_LOCALPLAYER_LOCAL_PLAYER_H_
