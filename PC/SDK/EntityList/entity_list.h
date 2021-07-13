#ifndef ENTITY_LIST_H_
#define ENTITY_LIST_H_

#include "SDK/Entity/entity.h"

#include "Memory/memory.h"
#include "dump.h"

class EntityList {
 public:
  explicit EntityList(const Module& client);

  Entity GetEntity(int index) const;
  static bool CanBeEntity(int index);

 private:
  DWORD address_{0};
};

#endif  // ENTITY_LIST_H_
