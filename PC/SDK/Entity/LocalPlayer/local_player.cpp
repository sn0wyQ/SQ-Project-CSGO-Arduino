#include "local_player.h"

LocalPlayer::LocalPlayer(const Module& client)
  : Entity(Memory::Read<DWORD>(client.base + Signatures::dwLocalPlayer)) {}

int LocalPlayer::GetCrosshairId() const {
    return Memory::Read<int>(this->GetAddress() + NetVars::m_iCrosshairId);
}
