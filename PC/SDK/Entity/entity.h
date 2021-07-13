#ifndef PC_SDK_ENTITY_ENTITY_H_
#define PC_SDK_ENTITY_ENTITY_H_

#include "Memory/memory.h"
#include "dump.h"

enum class Team {
  kNone = 0,
  kSpectator,
  kTerrorist,
  kCounterTerrorist
};

// Entity Flags
#define FL_ON_GROUND    (1 << 0)
#define FL_DUCKING      (1 << 1)
#define FL_WATER_JUMP   (1 << 2)
#define FL_ON_TRAIN     (1 << 3)
#define FL_IN_RAIN      (1 << 4)
#define FL_FROZEN       (1 << 5)
#define FL_AT_CONTROLS  (1 << 6)
#define FL_CLIENT       (1 << 7)
#define FL_FAKE_CLIENT  (1 << 8)
#define FL_IN_WATER     (1 << 9)

class Entity {
 public:
  explicit Entity(DWORD address);

  DWORD GetAddress() const;

  int GetHP() const;
  bool IsAlive() const;

  Team GetTeam() const;

  int GetFlags() const;

  bool IsInAir() const;

 private:
  DWORD address_{0};
};

#endif  // PC_SDK_ENTITY_ENTITY_H_
