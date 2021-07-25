#ifndef ARDUINO_HELPERS_GLOBAL_H_
#define ARDUINO_HELPERS_GLOBAL_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Helpers/definitions.h"

namespace Global {

LiquidCrystal lcd_screen
    (LCD_PIN_RS, LCD_PIN_EN, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

unsigned int prev_press = 0;

bool is_anything_selected = false;
bool need_to_update_screen = true;

bool is_blinking = false;
uint8_t blink_col = 0;
uint8_t blink_row = 0;

byte menu_page = MENU_PAGE_WH;

byte wh_mode = WH_MODE_NEAREST;
byte wh_page = WH_PAGE_POS;
byte wh_player_index = 0;

byte bhop_button = BHOP_OFF;

byte trigger_bot_page = TRIGGER_PAGE_STATE;
byte trigger_bot_state = TRIGGER_OFF;
int trigger_bot_delay = 0;
unsigned int trigger_bot_delay_start = 0;

byte aim_bot_page = AIM_PAGE_STATE;
byte aim_bot_state = AIM_OFF;
byte aim_bot_bone = AIM_BONE_HEAD;

}  // namespace Global

#endif  // ARDUINO_HELPERS_GLOBAL_H_
