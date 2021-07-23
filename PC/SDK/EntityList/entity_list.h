#ifndef PC_SDK_ENTITYLIST_ENTITY_LIST_H_
#define PC_SDK_ENTITYLIST_ENTITY_LIST_H_

#include "SDK/Entity/entity.h"

#include "Memory/memory.h"
#include "Utils/utils.h"
#include "dump.h"

class EntityList {
 public:
  explicit EntityList(const Module& client);

  Entity GetEntity(int id) const;
  static bool CanBeEntity(int id);

 private:
  DWORD address_{0};
};

#endif  // PC_SDK_ENTITYLIST_ENTITY_LIST_H_
