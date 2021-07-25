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
  Global::lcd_screen.clear();
  Utils::LoadIcons();

  Mouse.begin();
  Keyboard.begin();

  Utils::LoadAllSettings();
}

void loop() {
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
        if (Global::trigger_bot_state == TRIGGER_ON) {
          if (!Global::trigger_bot_delay) {
            Mouse.click(MOUSE_LEFT);
          } else {
            if (!Global::trigger_bot_delay_start) {
              Global::trigger_bot_delay_start = millis();
            }
          }
        }
        break;
      }

      case CMD_AIM: {
        // We must read |delta_x| and |delta_y|!
        // (Else they will be read as command)
        char delta_x = static_cast<char>(Serial.read());
        char delta_y = static_cast<char>(Serial.read());
        if (Global::aim_bot_state == AIM_ON) {
          Mouse.move(delta_x, delta_y, 0);
        }
        break;
      }

      default: {
        Utils::SendResponse(ARD_ER_UNKNOWN_CMD);
        break;
      }
    }
  }

  if (Global::trigger_bot_delay_start
      && (millis() - Global::trigger_bot_delay_start)
         > Global::trigger_bot_delay) {
    Mouse.click(MOUSE_LEFT);
    Global::trigger_bot_delay_start = 0;
  }

  if (Global::need_to_update_screen) {
    Utils::UpdateScreen();
  }

  switch (Utils::GetKeypadButton()) {
    case KP_NONE: {
      break;
    }

    case KP_RIGHT: {
      Utils::OnKpRightClicked();
      break;
    }

    case KP_UP: {
      Utils::OnKpUpClicked();
      break;
    }

    case KP_DOWN: {
      Utils::OnKpDownClicked();
      break;
    }

    case KP_LEFT: {
      Utils::OnKpLeftClicked();
      break;
    }

    case KP_SELECT: {
      Utils::OnKpSelectClicked();
      break;
    }
  }
}
