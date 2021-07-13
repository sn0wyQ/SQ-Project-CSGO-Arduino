#include <Arduino.h>
#include <HID.h>
#include <Keyboard.h>
#include <LiquidCrystal.h>
#include <Mouse.h>

#include "Helpers/definitions.h"
#include "Helpers/global.h"
#include "Helpers/utils.h"

void setup() {
  Serial.begin(128000);

  Global::lcd_screen.begin(16, 2);

  Mouse.begin();
  Keyboard.begin();

  Utils::Load(BHOP_BTN_ADDR, &Global::bhop_button);
}

void loop() {
  static bool need_to_update_screen = true;
  if (Serial.available()) {
    int cmd = Serial.read();
    switch (cmd) {
      case CMD_JUMP: {
        if (Global::bhop_button == BHOP_BTN_SPACE) {
          Keyboard.write(' ');
        } else if (Global::bhop_button == BHOP_BTN_MWHUP) {
          Mouse.move(0, 0, 127);
        }
        break;
      }

      case CMD_SHOOT: {
        Mouse.click(MOUSE_LEFT);
        break;
      }


      default: {
        // TODO(sn0wyQ): Display some error
        break;
      }
    }
  }

  if (need_to_update_screen) {
    Utils::UpdateScreen();
    need_to_update_screen = false;
  }

  // TODO(sn0wyQ): Beautify following maybe?
  switch (Utils::GetKeypadButton()) {
    case KP_NONE: {
      break;
    }

    case KP_RIGHT: {
      if (!Global::is_anything_selected) {
        ++Global::menu_page;
        if (Global::menu_page >= MENU_PAGE_MAX) {
          Global::menu_page = 0;
        }
        need_to_update_screen = true;
      }
      break;
    }

    case KP_UP: {
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

        default: {
          // TODO(sn0wyQ): Display some error
          break;
        }
      }
      need_to_update_screen = true;
      break;
    }

    case KP_DOWN: {
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

        default: {
          // TODO(sn0wyQ): Display some error
          break;
        }
      }
      need_to_update_screen = true;
      break;
    }

    case KP_LEFT: {
      if (!Global::is_anything_selected) {
        if (Global::menu_page == 0) {
          Global::menu_page = MENU_PAGE_MAX - 1;
        } else {
          --Global::menu_page;
        }
        need_to_update_screen = true;
      }
      break;
    }

    case KP_SELECT: {
      need_to_update_screen = true;
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
            Global::lcd_screen.setCursor(10, 1);
            Global::lcd_screen.blink();
          } else {
            Global::lcd_screen.noBlink();
          }
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
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
}
