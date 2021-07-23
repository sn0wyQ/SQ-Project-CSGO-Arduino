#ifndef PC_SDK_ENTITY_LOCALPLAYER_ABSTRACT_LOCAL_PLAYER_H_
#define PC_SDK_ENTITY_LOCALPLAYER_ABSTRACT_LOCAL_PLAYER_H_

#include "SDK/Entity/entity.h"

class AbstractLocalPlayer : public Entity {
 public:
  explicit AbstractLocalPlayer(DWORD address) : Entity(address) {}

  virtual float GetSensitivity() const = 0;
};

#endif  // PC_SDK_ENTITY_LOCALPLAYER_ABSTRACT_LOCAL_PLAYER_H_
