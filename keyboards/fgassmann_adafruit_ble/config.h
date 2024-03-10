

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER Florian Gassmann
#define PRODUCT      fgassmann_adafruit_ble

/* key matrix size */
//#define MATRIX_ROWS 1
//#define MATRIX_COLS 3

#define ENCODER_RESOLUTION 1


#define DIRECT_PINS { { F5, F4, F1 } }
#define ENCODERS_PAD_A { F7 }
#define ENCODERS_PAD_B { F6 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6


#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
