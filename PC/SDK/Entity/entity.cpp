#include "entity.h"

Entity::Entity(DWORD address) : address_(address) {}

DWORD Entity::GetAddress() const {
  return address_;
}

int Entity::GetHP() const {
  return Memory::Read<int>(address_ + NetVars::m_iHealth);
}

bool Entity::IsAlive() const {
  return (this->GetHP() > 0);
}

Team Entity::GetTeam() const {
  return static_cast<Team>(Memory::Read<int>(address_ + NetVars::m_iTeamNum));
}

int Entity::GetFlags() const {
  return Memory::Read<int>(address_ + NetVars::m_fFlags);
}

bool Entity::IsInAir() const {
  return !(this->GetFlags() & FL_ON_GROUND);
}
