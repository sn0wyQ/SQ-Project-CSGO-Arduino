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

bool Entity::IsDormant() const {
  return Memory::Read<bool>(address_ + Signatures::m_bDormant);
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

Vector Entity::GetPos() const {
  return Memory::Read<Vector>(address_ + NetVars::m_vecOrigin);
}

Vector Entity::GetViewAngle() const {
  return Memory::Read<Vector>(address_ + NetVars::m_vecViewOffset);
}

Vector Entity::GetView() const {
  return (this->GetPos() + this->GetViewAngle());
}

Vector Entity::GetBonePos(int bone) const {
  const auto matrix_address =
      Memory::Read<DWORD>(address_ + NetVars::m_dwBoneMatrix);
  return Vector(Memory::Read<float>(matrix_address + (0x30 * bone) + 0xC),
                Memory::Read<float>(matrix_address + (0x30 * bone) + 0x1C),
                Memory::Read<float>(matrix_address + (0x30 * bone) + 0x2C));
}
