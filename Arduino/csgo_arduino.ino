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

    default: {
      // TODO(sn0wyQ): Display some error
      break;
    }
  }
}
