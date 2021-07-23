#include "entity_list.h"

EntityList::EntityList(const Module& client) {
  address_ = client.base + Signatures::dwEntityList;
}

Entity EntityList::GetEntity(int id) const {
  return Entity(Memory::Read<DWORD>(address_ + ((id - 1) * 0x10)));
}

bool EntityList::CanBeEntity(int id) {
  return (id > 0 && id <= 64);
}
