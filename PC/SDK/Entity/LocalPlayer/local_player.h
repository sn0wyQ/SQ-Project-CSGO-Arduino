#ifndef LOCAL_PLAYER_H_
#define LOCAL_PLAYER_H_

#include "SDK/Entity/entity.h"

#include "Memory/memory.h"
#include "dump.h"

class LocalPlayer : public Entity {
 public:
  explicit LocalPlayer(const Module& client);

  int GetCrosshairId() const;
};

#endif  // LOCAL_PLAYER_H_
