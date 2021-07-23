#ifndef ABSTRACT_LOCAL_PLAYER_H_
#define ABSTRACT_LOCAL_PLAYER_H_

#include "SDK/Entity/entity.h"

class AbstractLocalPlayer : public Entity {
 public:
  explicit AbstractLocalPlayer(DWORD address) : Entity(address) {}

  virtual float GetSensitivity() const = 0;
};

#endif  // ABSTRACT_LOCAL_PLAYER_H_
