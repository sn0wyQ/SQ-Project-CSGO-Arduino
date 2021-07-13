#ifndef PC_MEMORY_MEMORY_H_
#define PC_MEMORY_MEMORY_H_

#include <Windows.h>
#include <TlHelp32.h>

struct Module {
  DWORD base;
  DWORD size;
};

// Singleton-based
class Memory {
 public:
  Memory(const Memory&) = delete;
  Memory& operator=(Memory&) = delete;

  static bool Attach(const char* process_name, DWORD access);
  static void Detach();

  static Module GetModule(const char* module_name);

  template<class T>
  static T Read(const DWORD address) {
    T result;
    Get()->Read_(address, &result);
    return result;
  }

  template<class T>
  static void Write(const DWORD address, const T& value) {
    Get()->Write_(address, value);
  }

 private:
  Memory() = default;

  static Memory* Get();

  bool Attach_(const char* process_name, DWORD access);
  void Detach_();

  Module GetModule_(const char* module_name) const;

  template<class T>
  void Read_(const DWORD address, T* result) {
    ReadProcessMemory(process_, reinterpret_cast<LPCVOID>(address),
                      result, sizeof(T), NULL);
  }

  template<class T>
  void Write_(const DWORD address, const T& value) {
    WriteProcessMemory(process_, reinterpret_cast<LPCVOID>(address),
                       &value, sizeof(T), NULL);
  }

  HANDLE process_{nullptr};
  DWORD pid_{NULL};

  static Memory* memory_;
};

#endif  // PC_MEMORY_MEMORY_H_
