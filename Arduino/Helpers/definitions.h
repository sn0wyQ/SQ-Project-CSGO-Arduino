#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// LCD Interface Pins
#define LCD_PIN_RS 8
#define LCD_PIN_EN 9
#define LCD_PIN_D4 4
#define LCD_PIN_D5 5
#define LCD_PIN_D6 6
#define LCD_PIN_D7 7

// Keypad buttons
#define KP_RIGHT  0
#define KP_UP     1
#define KP_DOWN   2
#define KP_LEFT   3
#define KP_SELECT 4
#define KP_NONE   5

// Commands
#define CMD_JUMP    0
#define CMD_SHOOT   1

// Menu pages
#define MENU_PAGE_WH       0
#define MENU_PAGE_BHOP     1
#define MENU_PAGE_TRIGGER  2
#define MENU_PAGE_AIM      3
#define MENU_PAGE_MAX      4

// WallHack modes
#define WH_MODE_NEAREST 0
#define WH_MODE_PLAYER  1
#define WH_MODE_MAX     2

// WallHack pages
#define WH_PAGE_POS 0
#define WH_PAGE_INV 1
#define WH_PAGE_MAX 2

// BunnyHop buttons
#define BHOP_OFF          0
#define BHOP_BTN_SPACE    1
#define BHOP_BTN_MWHUP    2
#define BHOP_BTN_MAX      3

// Settings addresses
#define BHOP_BTN_ADDR 0 // (size - 1 byte)

// Limits
#define MAX_MOUSE_MOVE_LENGTH 127

#endif  // DEFINITIONS_H_
