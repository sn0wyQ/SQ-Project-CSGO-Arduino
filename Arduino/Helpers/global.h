#ifndef ARDUINO_HELPERS_GLOBAL_H_
#define ARDUINO_HELPERS_GLOBAL_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Helpers/definitions.h"

namespace Global {

LiquidCrystal lcd_screen
    (LCD_PIN_RS, LCD_PIN_EN, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

bool is_anything_selected = false;

byte menu_page = MENU_PAGE_WH;

byte wh_mode = WH_MODE_NEAREST;
byte wh_page = WH_PAGE_POS;
byte wh_player_index = 0;

byte bhop_button = BHOP_OFF;

}  // namespace Global

#endif  // ARDUINO_HELPERS_GLOBAL_H_
