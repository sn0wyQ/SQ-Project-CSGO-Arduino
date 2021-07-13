#include "memory.h"

Memory* Memory::memory_ = nullptr;

Memory* Memory::Get() {
  if (!memory_) {
    memory_ = new Memory();
  }
  return memory_;
}

bool Memory::Attach(const char* process_name, DWORD access) {
  return Get()->Attach_(process_name, access);
}

bool Memory::Attach_(const char* process_name, DWORD access) {
  HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(entry);

  do {
    if (!strcmp(entry.szExeFile, process_name)) {
      pid_ = entry.th32ProcessID;
      CloseHandle(handle);
      process_ = OpenProcess(access, false, pid_);
      return true;
    }
  } while (Process32Next(handle, &entry));

  return false;
}

void Memory::Detach() {
  Get()->Detach_();
}

void Memory::Detach_() {
  CloseHandle(process_);
}

Module Memory::GetModule(const char* module_name) {
  return Get()->GetModule_(module_name);
}

Module Memory::GetModule_(const char* module_name) const {
  HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid_);

  MODULEENTRY32 entry;
  entry.dwSize = sizeof(entry);

  do {
    if (!strcmp(entry.szModule, module_name)) {
      CloseHandle(module);
      return Module{reinterpret_cast<DWORD>(entry.hModule), entry.modBaseSize};
    }
  } while (Module32Next(module, &entry));

  return Module{0, 0};
}
