#include "arduino.h"

HANDLE Arduino::arduino_handle_ = nullptr;

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
    Utils::Log("[ARDUINO] Error #% during CreateFile", last_error);
    return;
  }


  DCB dcb = {};
  dcb.DCBlength = sizeof(dcb);
  if (!GetCommState(arduino_handle_, &dcb)) {
    DWORD last_error = ::GetLastError();
    Utils::Log("[ARDUINO] Error #% during GetCommState", last_error);
    return;
  }

  dcb.BaudRate = CBR_128000;
  dcb.ByteSize = 8;
  dcb.StopBits = ONESTOPBIT;
  dcb.Parity = NOPARITY;

  if (!SetCommState(arduino_handle_, &dcb)) {
    DWORD last_error = ::GetLastError();
    Utils::Log("[ARDUINO] Error #% during SetCommState", last_error);
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
    Utils::Log("[ARDUINO] Error #% during SetCommTimeouts", last_error);
    return;
  }

  Utils::Log("[ARDUINO] Connected to Arduino Leonardo at %", com_port);
}

Arduino::~Arduino() {
  CloseHandle(arduino_handle_);
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

  return SendData(cmd.c_str(), cmd.length() + 1);
}

bool Arduino::SendData(const char* data, SIZE_T data_size) {
  DWORD bytes_written = 0;
  return WriteFile(arduino_handle_, data, data_size, &bytes_written, nullptr);
}

bool Arduino::ReadByte(char* byte) {
  DWORD bytes_read;
  return ReadFile(arduino_handle_,
                  byte,
                  1,
                  &bytes_read,
                  nullptr);
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
