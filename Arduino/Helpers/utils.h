#ifndef ARDUINO_HELPERS_UTILS_H_
#define ARDUINO_HELPERS_UTILS_H_

#include <stdarg.h>

#include <Arduino.h>
#include <EEPROM.h>

#include "Helpers/arrays.h"
#include "Helpers/bytes.h"
#include "Helpers/definitions.h"
#include "Helpers/global.h"

namespace Utils {

inline byte GetKeypadButton() {
  int adc_key_in = analogRead(0);
  if (millis() - Global::prev_press > 250) {
    if (adc_key_in >= 700) {
      return KP_NONE;
    }
    Global::prev_press = millis();
    if (adc_key_in < 30) {
      return KP_RIGHT;
    } else if (adc_key_in > 70 && adc_key_in < 150) {
      return KP_UP;
    } else if (adc_key_in > 200 && adc_key_in < 320) {
      return KP_DOWN;
    } else if (adc_key_in > 350 && adc_key_in < 500) {
      return KP_LEFT;
    } else if (adc_key_in > 570 && adc_key_in < 700) {
      return KP_SELECT;
    }
  }
  return KP_NONE;
}

template <typename T>
void Save(int address, const T& data) {
  EEPROM.put(address, data);
}

template <typename T>
void Load(int address, T* data) {
  EEPROM.get(address, *data);
}

inline void LoadAllSettings() {
  Utils::Load(BHOP_BTN_ADDR, &Global::bhop_button);

  Utils::Load(TRIGGER_STATE_ADDR, &Global::trigger_bot_state);
  Utils::Load(TRIGGER_DELAY_ADDR, &Global::trigger_bot_delay);

  Utils::Load(AIM_STATE_ADDR, &Global::aim_bot_state);
  Utils::Load(AIM_BONE_ADDR, &Global::aim_bot_bone);
}

void SendResponse(char response) {
  if (Serial.availableForWrite()) {
    Serial.write(response);
  }
}

template <class ...Ts>
void SendResponse(char response, const Ts& ...args) {
  if (Serial.availableForWrite()) {
    Serial.write(response);
    Serial.write(args...);
  }
}

void StartBlinking(uint8_t col, uint8_t row) {
  Global::is_blinking = true;
  Global::blink_col = col;
  Global::blink_row = row;
  Global::need_to_update_screen = true;
}

void StopBlinking() {
  Global::is_blinking = false;
  Global::need_to_update_screen = true;
}

void PrintWithMoreSpaces(const String& str, byte wanted_length) {
  for (byte i = wanted_length - str.length(); i > 0; --i) {
    Global::lcd_screen.write(' ');
  }
  Global::lcd_screen.print(str);
}

void PrintWithMoreZeros(int value, byte wanted_length) {
  String str(value);
  for (byte i = wanted_length - str.length(); i > 0; --i) {
    Global::lcd_screen.write('0');
  }
  Global::lcd_screen.print(str);
}

inline void UpdateScreen() {
  Global::need_to_update_screen = false;
  Global::lcd_screen.clear();


  switch (Global::menu_page) {
    case MENU_PAGE_WH: {
      switch (Global::wh_mode) {
        case WH_MODE_NEAREST: {
          Global::lcd_screen.print("Nearest");
          break;
        }

        case WH_MODE_PLAYER: {
          // TODO(sn0wyQ): Print player nickname (up to 10 symbols)
          break;
        }

        default: {
          // TODO(sn0wyQ): Display some error
          break;
        }
      }

      Global::lcd_screen.setCursor(10, 0);
      Global::lcd_screen.write(ICON_WALL);
      // TODO(sn0wyQ): Print weapon (up to 3 symbols)
      // TODO(sn0wyQ): Vest(helm) icon if needed
      // TODO(sn0wyQ): Bomb/kit icon if needed

      Global::lcd_screen.setCursor(0, 1);
      switch (Global::wh_page) {
        case WH_PAGE_POS: {
          // TODO(sn0wyQ): Print player position (up to 11 symbols)
          Global::lcd_screen.setCursor(11, 1);
          Global::lcd_screen.write(ICON_WALL);
          // TODO(sn0wyQ): Print player hp (3 symbols)
          Global::lcd_screen.write(ICON_HEART);
          break;
        }

        case WH_PAGE_INV: {
          // TODO(sn0wyQ): Print player armor hp (3 symbols)
          Global::lcd_screen.write(ICON_VEST);
          Global::lcd_screen.write(ICON_WALL);
          // TODO(sn0wyQ): Print player money (5 symbols)
          Global::lcd_screen.write(' ');
          Global::lcd_screen.write(ICON_WALL);
          // TODO(sn0wyQ): Print player hp (3 symbols)
          Global::lcd_screen.write(ICON_HEART);
          break;
        }

        default: {
          // TODO(sn0wyQ): Display some error
          break;
        }
      }
      break;
    }

    case MENU_PAGE_BHOP: {
      Global::lcd_screen.print("Bunny Hop v1.0");
      Global::lcd_screen.setCursor(0, 1);
      Global::lcd_screen.print("Button");
      Global::lcd_screen.setCursor(9, 1);
      Global::lcd_screen.write(ICON_WALL);
      Utils::PrintWithMoreSpaces(Arrays::kBhopBtns[Global::bhop_button], 6);
      break;
    }

    case MENU_PAGE_TRIGGER: {
      Global::lcd_screen.print("Trigger Bot v1.1");
      Global::lcd_screen.setCursor(0, 1);
      switch (Global::trigger_bot_page) {
        case TRIGGER_PAGE_STATE: {
          Global::lcd_screen.print("Activate");
          Global::lcd_screen.setCursor(11, 1);
          Global::lcd_screen.write(ICON_WALL);
          Utils::PrintWithMoreSpaces(Arrays::kState[Global::trigger_bot_state],
                                     4);
          break;
        }

        case TRIGGER_PAGE_DELAY: {
          Global::lcd_screen.print("Delay (ms)");
          Global::lcd_screen.setCursor(11, 1);
          Global::lcd_screen.write(ICON_WALL);
          Global::lcd_screen.write(' ');
          Utils::PrintWithMoreZeros(Global::trigger_bot_delay, 3);
          break;
        }

        default: {
          // TODO(sn0wyQ): Display some error
          break;
        }
      }
      break;
    }

    case MENU_PAGE_AIM: {
      Global::lcd_screen.print("Aim Bot v1.1");
      Global::lcd_screen.setCursor(0, 1);
      switch (Global::aim_bot_page) {
        case AIM_PAGE_STATE: {
          Global::lcd_screen.print("Activate");
          Global::lcd_screen.setCursor(11, 1);
          Global::lcd_screen.write(ICON_WALL);
          Utils::PrintWithMoreSpaces(Arrays::kState[Global::aim_bot_state], 4);
          break;
        }

        case AIM_PAGE_BONE: {
          Global::lcd_screen.print("Bone");
          Global::lcd_screen.setCursor(7, 1);
          Global::lcd_screen.write(ICON_WALL);
          Utils::PrintWithMoreSpaces(Arrays::kBoneNames[Global::aim_bot_bone],
                                     8);
          break;
        }

        default: {
          // TODO(sn0wyQ): Display some error
          break;
        }
      }
      break;
    }

    default: {
      Global::lcd_screen.print("Error:");
      Global::lcd_screen.setCursor(0, 1);
      Global::lcd_screen.print("Unknown page");
      break;
    }
  }

  if (Global::is_blinking) {
    Global::lcd_screen.setCursor(Global::blink_col, Global::blink_col);
    Global::lcd_screen.blink();
  } else {
    Global::lcd_screen.noBlink();
  }
}

void LoadIcons() {
  switch (Global::menu_page) {
    case MENU_PAGE_WH: {
      Global::lcd_screen.createChar(ICON_WALL, Bytes::kWall);
      Global::lcd_screen.createChar(ICON_LOCK_CLOSED, Bytes::kLockClosed);
      Global::lcd_screen.createChar(ICON_LOCK_OPENED, Bytes::kLockOpened);
      Global::lcd_screen.createChar(ICON_HEART, Bytes::kHeart);
      Global::lcd_screen.createChar(ICON_C4, Bytes::kC4);
      Global::lcd_screen.createChar(ICON_KIT, Bytes::kKit);
      Global::lcd_screen.createChar(ICON_VEST, Bytes::kVest);
      Global::lcd_screen.createChar(ICON_VEST_HELM, Bytes::kVestHelm);
      break;
    }

    case MENU_PAGE_BHOP: {
      Global::lcd_screen.createChar(ICON_WALL, Bytes::kWall);
      break;
    }

    case MENU_PAGE_TRIGGER: {
      Global::lcd_screen.createChar(ICON_WALL, Bytes::kWall);
      break;
    }

    case MENU_PAGE_AIM: {
      Global::lcd_screen.createChar(ICON_WALL, Bytes::kWall);
      break;
    }

    default: {
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
}

inline void OnKpRightClicked() {
  if (!Global::is_anything_selected) {
    ++Global::menu_page;
    if (Global::menu_page >= MENU_PAGE_MAX) {
      Global::menu_page = 0;
    }
    Utils::LoadIcons();
    Global::need_to_update_screen = true;
  }
}

inline void OnKpUpClicked() {
  switch (Global::menu_page) {
    case MENU_PAGE_WH: {
      ++Global::wh_mode;
      if (Global::wh_mode >= WH_MODE_MAX) {
        Global::wh_mode = 0;
      }
      break;
    }

    case MENU_PAGE_BHOP: {
      if (Global::is_anything_selected) {
        ++Global::bhop_button;
        if (Global::bhop_button >= BHOP_BTN_MAX) {
          Global::bhop_button = 0;
        }
        Utils::Save(BHOP_BTN_ADDR, Global::bhop_button);
      }
      break;
    }

    case MENU_PAGE_TRIGGER: {
      if (Global::is_anything_selected) {
        switch (Global::trigger_bot_page) {
          case TRIGGER_PAGE_STATE: {
            ++Global::trigger_bot_state;
            if (Global::trigger_bot_state >= TRIGGER_MAX) {
              Global::trigger_bot_state = 0;
            }
            Utils::Save(TRIGGER_STATE_ADDR, Global::trigger_bot_state);
            break;
          }

          case TRIGGER_PAGE_DELAY: {
            ++Global::trigger_bot_delay;
            if (Global::trigger_bot_delay > TRIGGER_MAX_DELAY) {
              Global::trigger_bot_delay = 0;
            }
            Utils::Save(TRIGGER_DELAY_ADDR, Global::trigger_bot_delay);
            break;
          }

          default: {
            // TODO(sn0wyQ): Display some error
            break;
          }
        }
      } else {
        ++Global::trigger_bot_page;
        if (Global::trigger_bot_page >= TRIGGER_PAGE_MAX) {
          Global::trigger_bot_page = 0;
        }
      }
      break;
    }

    case MENU_PAGE_AIM: {
      if (Global::is_anything_selected) {
        switch (Global::aim_bot_page) {
          case AIM_PAGE_STATE: {
            ++Global::aim_bot_state;
            if (Global::aim_bot_state >= AIM_MAX) {
              Global::aim_bot_state = 0;
            }
            Utils::Save(AIM_STATE_ADDR, Global::aim_bot_state);
            break;
          }

          case AIM_PAGE_BONE: {
            ++Global::aim_bot_bone;
            if (Global::aim_bot_bone >= AIM_BONE_MAX) {
              Global::aim_bot_bone = 0;
            }
            Utils::SendResponse(ARD_CMD_SET_BONE, Global::aim_bot_bone);
            Utils::Save(AIM_BONE_ADDR, Global::aim_bot_bone);
            break;
          }

          default: {
            // TODO(sn0wyQ): Display some error
            break;
          }
        }
      } else {
        ++Global::aim_bot_page;
        if (Global::aim_bot_page >= AIM_PAGE_MAX) {
          Global::aim_bot_page = 0;
        }
      }
      break;
    }

    default: {
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
  Global::need_to_update_screen = true;
}

inline void OnKpDownClicked() {
  switch (Global::menu_page) {
    case MENU_PAGE_WH: {
      if (Global::wh_mode == 0) {
        Global::wh_mode = WH_MODE_MAX - 1;
      } else {
        --Global::wh_mode;
      }
      break;
    }

    case MENU_PAGE_BHOP: {
      if (Global::is_anything_selected) {
        if (Global::bhop_button == 0) {
          Global::bhop_button = BHOP_BTN_MAX - 1;
        } else {
          --Global::bhop_button;
        }
        Utils::Save(BHOP_BTN_ADDR, Global::bhop_button);
      }
      break;
    }

    case MENU_PAGE_TRIGGER: {
      if (Global::is_anything_selected) {
        switch (Global::trigger_bot_page) {
          case TRIGGER_PAGE_STATE: {
            if (Global::trigger_bot_state == 0) {
              Global::trigger_bot_state = TRIGGER_MAX - 1;
            } else {
              --Global::trigger_bot_state;
            }
            Utils::Save(TRIGGER_STATE_ADDR, Global::trigger_bot_state);
            break;
          }

          case TRIGGER_PAGE_DELAY: {
            if (Global::trigger_bot_delay == 0) {
              Global::trigger_bot_delay = TRIGGER_MAX_DELAY;
            } else {
              --Global::trigger_bot_delay;
            }
            Utils::Save(TRIGGER_DELAY_ADDR, Global::trigger_bot_delay);
            break;
          }

          default: {
            // TODO(sn0wyQ): Display some error
            break;
          }
        }
      } else {
        if (Global::trigger_bot_page == 0) {
          Global::trigger_bot_page = TRIGGER_PAGE_MAX - 1;
        } else {
          --Global::trigger_bot_page;
        }
      }
      break;
    }

    case MENU_PAGE_AIM: {
      if (Global::is_anything_selected) {
        switch (Global::aim_bot_page) {
          case AIM_PAGE_STATE: {
            if (Global::aim_bot_state == 0) {
              Global::aim_bot_state = AIM_MAX - 1;
            } else {
              --Global::aim_bot_state;
            }
            Utils::Save(AIM_STATE_ADDR, Global::aim_bot_state);
          }

          case AIM_PAGE_BONE: {
            if (Global::aim_bot_bone == 0) {
              Global::aim_bot_bone = AIM_BONE_MAX - 1;
            } else {
              --Global::aim_bot_bone;
            }
            Utils::SendResponse(ARD_CMD_SET_BONE, Global::aim_bot_bone);
            Utils::Save(AIM_BONE_ADDR, Global::aim_bot_bone);
          }

          default: {
            // TODO(sn0wyQ): Display some error
            break;
          }
        }
      } else {
        if (Global::aim_bot_page == 0) {
          Global::aim_bot_page = AIM_PAGE_MAX - 1;
        } else {
          --Global::aim_bot_page;
        }
      }
      break;
    }

    default: {
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
  Global::need_to_update_screen = true;
}

inline void OnKpLeftClicked() {
  if (!Global::is_anything_selected) {
    if (Global::menu_page == 0) {
      Global::menu_page = MENU_PAGE_MAX - 1;
    } else {
      --Global::menu_page;
    }
    Utils::LoadIcons();
    Global::need_to_update_screen = true;
  }
}

inline void OnKpSelectClicked() {
  switch (Global::menu_page) {
    case MENU_PAGE_WH: {
      ++Global::wh_page;
      if (Global::wh_mode >= WH_PAGE_POS) {
        Global::wh_page = 0;
      }
      break;
    }

    case MENU_PAGE_BHOP: {
      Global::is_anything_selected = !Global::is_anything_selected;
      if (Global::is_anything_selected) {
        Utils::StartBlinking(10, 1);
      } else {
        Utils::StopBlinking();
      }
      break;
    }

    case MENU_PAGE_TRIGGER: {
      Global::is_anything_selected = !Global::is_anything_selected;
      if (Global::is_anything_selected) {
        Utils::StartBlinking(12, 1);
      } else {
        Utils::StopBlinking();
      }
      break;
    }

    case MENU_PAGE_AIM: {
      Global::is_anything_selected = !Global::is_anything_selected;
      if (Global::is_anything_selected) {
        switch (Global::aim_bot_page) {
          case AIM_PAGE_STATE: {
            Utils::StartBlinking(12, 1);
            break;
          }

          case AIM_PAGE_BONE: {
            Utils::StartBlinking(8, 1);
            break;
          }

          default: {
            // TODO(sn0wyQ): Display some error
            break;
          }
        }
      } else {
        Utils::StopBlinking();
      }
      break;
    }

    default: {
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
  Global::need_to_update_screen = true;
}

}  // namespace Utils

#endif  // ARDUINO_HELPERS_UTILS_H_
