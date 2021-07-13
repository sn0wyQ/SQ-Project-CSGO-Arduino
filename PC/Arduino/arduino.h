#ifndef ARDUINO_H_
#define ARDUINO_H_

#pragma comment(lib, "Setupapi.lib")

#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>

#include <string>
#include <vector>

#include "Utils/utils.h"

// Commands
#define CMD_JUMP    0
#define CMD_SHOOT   1
#define CMD_MAX     2

class Arduino {
 public:
  static void Connect(LPCSTR com_port);

  static bool SendCommand(char cmd_index, const std::vector<char>& params = {});
  static bool SendData(const char* data, SIZE_T data_size);

  static bool GetDevice(LPCSTR friendly_name, LPSTR com_port);

 private:
  Arduino() = default;
  ~Arduino();

  static HANDLE arduino_handle_;
};

#endif  // ARDUINO_H_
