#include "arduino.h"

HANDLE Arduino::arduino_handle_ = nullptr;

Arduino::~Arduino() {
  CloseHandle(arduino_handle_);
}

void Arduino::Connect(LPCSTR com_port) {
  arduino_handle_ = CreateFile(com_port,
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               nullptr,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               nullptr);
  if (!arduino_handle_) {
    DWORD last_error = ::GetLastError();
    Utils::Log("[ARDUINO] Error #% during CreateFile\n", last_error);
    return;
  }


  DCB dcb = {};
  dcb.DCBlength = sizeof(dcb);
  if (!GetCommState(arduino_handle_, &dcb)) {
    DWORD last_error = ::GetLastError();
    Utils::Log("[ARDUINO] Error #% during GetCommState\n", last_error);
    return;
  }

  dcb.BaudRate = CBR_128000;
  dcb.ByteSize = 8;
  dcb.StopBits = ONESTOPBIT;
  dcb.Parity = NOPARITY;

  if (!SetCommState(arduino_handle_, &dcb)) {
    DWORD last_error = ::GetLastError();
    Utils::Log("[ARDUINO] Error #% during SetCommState\n", last_error);
    return;
  }

  COMMTIMEOUTS cto = {};
  cto.ReadIntervalTimeout = 2;
  cto.ReadTotalTimeoutConstant = 2;
  cto.ReadTotalTimeoutMultiplier = 5;
  cto.WriteTotalTimeoutConstant = 2;
  cto.WriteTotalTimeoutMultiplier = 5;
  if (!SetCommTimeouts(arduino_handle_, &cto)) {
    DWORD last_error = ::GetLastError();
    Utils::Log("[ARDUINO] Error #% during SetCommTimeouts\n", last_error);
    return;
  }

  Arduino::UpdateConfig();

  Utils::Log("[ARDUINO] Connected to Arduino Leonardo at %\n", com_port);
}

void Arduino::UpdateConfig() {
  Arduino::SendCommand(CMD_UPDATE);
}

bool Arduino::SendCommand(char cmd_index, const std::vector<char>& params) {
  if (cmd_index >= CMD_MAX) {
    Utils::Log("[ARDUINO] Error: Trying to send unknown command (index %)"
               "to Arduino", cmd_index);
    return false;
  }

  std::string cmd(params.size() + 1, cmd_index);
  for (int i = 0; i < params.size(); ++i) {
    cmd.at(i + 1) = params.at(i);
  }

  return SendData(cmd.c_str(), cmd.length());
}

bool Arduino::SendData(const char* data, SIZE_T data_size) {
  DWORD bytes_written = 0;
  return WriteFile(arduino_handle_, data, data_size, &bytes_written, nullptr);
}

bool Arduino::ReadByte(char* byte) {
  DWORD bytes_read;
  ReadFile(arduino_handle_,
           byte,
           1,
           &bytes_read,
           nullptr);
  return (bytes_read == 1);
}

bool Arduino::Read32Bits(void* data) {
  DWORD bytes_read;
  ReadFile(arduino_handle_,
           data,
           4,
           &bytes_read,
           nullptr);
  return (bytes_read == 4);
}

bool Arduino::GetDevice(LPCSTR friendly_name, LPSTR com_port) {
  HDEVINFO device_info = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS,
                                             nullptr,
                                             nullptr,
                                             DIGCF_PRESENT);
  if (device_info == INVALID_HANDLE_VALUE) {
    return false;
  }

  SP_DEVINFO_DATA dev_info_data = {};
  dev_info_data.cbSize = sizeof(dev_info_data);

  DWORD device_count = 0;
  while (SetupDiEnumDeviceInfo(device_info, device_count++, &dev_info_data)) {
    BYTE buf[256] = {0};
    if (SetupDiGetDeviceRegistryProperty(device_info,
                                         &dev_info_data,
                                         SPDRP_FRIENDLYNAME,
                                         nullptr,
                                         buf,
                                         sizeof(buf),
                                         nullptr)) {
      LPCSTR port_name_pos = strstr(reinterpret_cast<LPCSTR>(buf), "COM");
      if (!port_name_pos) {
        continue;
      }

      DWORD out_buf_len = strlen(com_port);
      DWORD len = out_buf_len + strlen(port_name_pos);
      if (strstr(reinterpret_cast<LPCSTR>(buf), friendly_name)) {
        for (DWORD i = 0; i < len; ++i, ++out_buf_len) {
          com_port[out_buf_len] = port_name_pos[i];
        }
        com_port[strlen(com_port) - 1] = 0;
        return true;
      }
    }
  }

  return false;
}

void Arduino::CheckArduinoOutput() {
  char output;
  if (Arduino::ReadByte(&output)) {
    switch (output) {
      case ARD_ER_UNKNOWN_CMD: {
        Utils::Log("[ARDUINO] Internal Error: unknown command");
        break;
      }

      case ARD_CMD_SET_BONE: {
        if (Arduino::ReadByte(&output)) {
          Global::aim_bot_bone = Global::kBones[output];
          Utils::Log("[AIM BOT] Set bone to %", Global::aim_bot_bone);
        }
        break;
      }

      case ARD_CMD_SET_FOV: {
        float new_fov;
        if (Arduino::Read32Bits(&new_fov)) {
          Global::aim_bot_fov = new_fov;
          Utils::Log("[AIM BOT] Set FOV to %", Global::aim_bot_fov);
        }
        break;
      }

      case ARD_CMD_SET_SMOOTH: {
        float new_smooth;
        if (Arduino::Read32Bits(&new_smooth)) {
          Global::aim_bot_smooth = new_smooth;
          Utils::Log("[AIM BOT] Set smooth to %", Global::aim_bot_smooth);
        }
        break;
      }

      default: {
        Utils::Log("[ARDUINO] Error: Output \"%\" can not be recognized as "
                   "a valid response", output);
        break;
      }
    }
  }
}
