#ifndef CONFIG_H
#define CONFIG_H

// Basics
#define GSR_MINIMUM_BATTERY_VOLTAGE 0 // GSR uses higher, RTC based minimum voltage levels. Change this to 1 if you have problems at lower battery levels
#define DEBUG_MENUS 1                 // Includes debug menus for various things
#define VIBRATION_BUTTON_TIME 35      // Time in ms to the motor to vibrate after clicking a button. 0 means none
#define VIBRATION_ACTION_TIME 60      // Time in ms to the motor to vibrate when the UI receives an action
#define TIME_OFFSET_S 3600            // Time offset in seconds, use this as timezones
#define MENU_LINES false // Option to show lines between buttons in menus
#define BUTTON_LONG_PRESS_MS 500 // Duration until long press registers in miliseconds

// Advanced
#define SLEEP_EVERY_MS 180000 // Goes to sleep timer, is resetted by button presses
#define LOOP_DELAY 10         // Speed of the device basically
#define BUTTON_TASK_DELAY 140 // In ms, lower means faster button detection but more cpu usage

// Debugging help
#define DEBUG 1
#define EINK_COUNTER 0      // Shows a counter somewhere on screen
#define DUMP_INIT_DEBUG 1   // If debug, shows at init init information
#define DUMP_LOOP_DEBUG 0   // If debug, at every loop iteration dump hardware values that can change
#define SCREEN_SLEEP_INFO 1 // Shows information on screen when the device goes to screen
#define DRAW_DEBUG_RECT 0   // Shows rectangles where custom functions write bitmaps

// Display init magic ;)
#define EPD_CS 5
#define EPD_DC 10
#define EPD_RESET 9
#define EPD_BUSY 19

// Button pins
#define MENU_PIN 26
#define BACK_PIN 25
#define DOWN_PIN 4

// Button masks (for wake up)
#define MENU_MASK GPIO_SEL_26
#define BACK_MASK GPIO_SEL_25
#define DOWN_MASK GPIO_SEL_4

// Voltage reading average
#define VOLTAGE_AVG_COUNT 20
#define VOLTAGE_AVG_DELAY 5

// Battery
#define BATTERY_MIN_VOLTAGE 3.3
#define BATTERY_CRIT_VOLTAGE 3.15
#define BATTERY_MAX_VOLTAGE 4.27 // For calculating percentages, upper limit

// Other
#define VIB_MOTOR_PIN 13 // Vibration motor
#define MAX_MENU_ITEMS 20

#endif
