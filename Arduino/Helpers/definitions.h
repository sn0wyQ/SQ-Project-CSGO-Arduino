#ifndef ARDUINO_HELPERS_DEFINITIONS_H_
#define ARDUINO_HELPERS_DEFINITIONS_H_

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

#define KP_PRESS_DELAY 175

// Icons
// -- WallHack page
#define ICON_WALL         byte(0)
#define ICON_LOCK_CLOSED  byte(1)
#define ICON_LOCK_OPENED  byte(2)
#define ICON_HEART        byte(3)
#define ICON_C4           byte(4)
#define ICON_KIT          byte(5)
#define ICON_VEST         byte(6)
#define ICON_VEST_HELM    byte(7)
// -- BunnyHop page
// #define ICON_WALL      byte(0)
// -- TriggerBot page
// #define ICON_WALL      byte(0)
// -- AimBot page
// #define ICON_WALL      byte(0)

// Commands
#define CMD_JUMP    1  // No arguments
#define CMD_SHOOT   2  // No arguments
#define CMD_AIM     3  // x, y -> how much to move mouse to in X and Y axis
#define CMD_INFO    4  // n - number of NOT dormant enemies, then n player_infos
#define CMD_UPDATE  5  // No arguments

// Response codes
// -- Errors
#define ARD_ER_UNKNOWN_CMD  1
// -- Arduino Commands
#define ARD_CMD_SET_BONE    20
#define ARD_CMD_SET_FOV     21

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

// TriggerBot pages
#define TRIGGER_PAGE_STATE  0
#define TRIGGER_PAGE_DELAY  1
#define TRIGGER_PAGE_MAX    2

// TriggerBot states
#define TRIGGER_OFF 0
#define TRIGGER_ON  1
#define TRIGGER_MAX 2

#define TRIGGER_MAX_DELAY 999

// AimBot pages
#define AIM_PAGE_STATE  0
#define AIM_PAGE_BONE   1
#define AIM_PAGE_FOV    2
#define AIM_PAGE_MAX    3

// AimBot states
#define AIM_OFF 0
#define AIM_ON  1
#define AIM_MAX 2

// AimBot Bones
#define AIM_BONE_STOMACH  0
#define AIM_BONE_CHEST    1
#define AIM_BONE_NECK     2
#define AIM_BONE_HEAD     3
#define AIM_BONE_MAX      4

// Settings addresses
// -- BunnyHop
#define BHOP_BTN_ADDR       0  // (size - 1 byte)
// -- TriggerBot
#define TRIGGER_STATE_ADDR  1  // (size - 1 byte)
#define TRIGGER_DELAY_ADDR  2  // (size - 2 bytes)
// -- AimBot
#define AIM_STATE_ADDR      4  // (size - 1 byte)
#define AIM_BONE_ADDR       5  // (size - 1 byte)
#define AIM_FOV_ADDR        6  // (size - 4 bytes)

// Limits
#define MAX_MOUSE_MOVE_LENGTH 127

#endif  // ARDUINO_HELPERS_DEFINITIONS_H_
