#ifndef ARDUINO_HELPERS_UTILS_H_
#define ARDUINO_HELPERS_UTILS_H_

#include <Arduino.h>
#include <EEPROM.h>

#include "Helpers/arrays.h"
#include "Helpers/bytes.h"
#include "Helpers/definitions.h"
#include "Helpers/global.h"

namespace Utils {

byte GetKeypadButton() {
  static unsigned int prev_press = millis();
  int adc_key_in = analogRead(0);
  if (millis() - prev_press > 250) {
    if (adc_key_in >= 800) {
      return KP_NONE;
    }
    prev_press = millis();
    if (adc_key_in < 70) {
      return KP_RIGHT;
    } else if (adc_key_in < 250) {
      return KP_UP;
    } else if (adc_key_in < 400) {
      return KP_DOWN;
    } else if (adc_key_in < 550) {
      return KP_LEFT;
    } else {
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

void UpdateScreen() {
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
      Global::lcd_screen.write('|');
      // TODO(sn0wyQ): Print weapon (up to 3 symbols)
      // TODO(sn0wyQ): Vest(helm) icon
      // TODO(sn0wyQ): Bomb/kit icon

      Global::lcd_screen.setCursor(0, 1);
      switch (Global::wh_page) {
        case WH_PAGE_POS: {
          // TODO(sn0wyQ): Print player position (up to 11 symbols)
          Global::lcd_screen.write('|');
          // TODO(sn0wyQ): Print player hp (up to 3 symbols)
          Global::lcd_screen.write('+');
          break;
        }

        case WH_PAGE_INV: {
          // TODO(sn0wyQ): Print player nades (up to 4 symbols)
          Global::lcd_screen.write('|');
          // TODO(sn0wyQ): Print player money (up to 5 symbols)
          Global::lcd_screen.print("$|");
          // TODO(sn0wyQ): Print player hp (up to 3 symbols)
          Global::lcd_screen.write('+');
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
      Global::lcd_screen.print("Bunny Hop  | ");
      // TODO(sn0wyQ): Print "ON"/"OFF" ("ON" if bhop_button on PC is active)
      Global::lcd_screen.setCursor(0, 1);
      Global::lcd_screen.print("Button   | ");
      for (byte i = 5 - Arrays::kBhopBtns[Global::bhop_button].length();
           i > 0; --i) {
        Global::lcd_screen.write(' ');
      }
      Global::lcd_screen.print(Arrays::kBhopBtns[Global::bhop_button]);
      break;
    }

    default: {
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
}

}  // namespace Utils

#endif  // ARDUINO_HELPERS_UTILS_H_
