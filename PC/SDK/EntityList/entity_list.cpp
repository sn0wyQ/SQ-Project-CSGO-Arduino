#include "entity_list.h"

EntityList::EntityList(const Module& client) {
  address_ = Memory::Read<DWORD>(client.base + Signatures::dwEntityList);
}

Entity EntityList::GetEntity(int index) const {
  return Entity(Memory::Read<DWORD>(address_ + ((index - 1) * 0x10)));
}

bool EntityList::CanBeEntity(int index) {
  return (index > 0 && index <= 64);
}
