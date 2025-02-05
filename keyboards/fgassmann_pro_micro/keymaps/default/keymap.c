/* Copyright 2022 Florian Gassmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

//#include "analog.c"
#include "analog.h"
#include "math.h"
//#include "pincontrol.h"

#include "print.h"
#include "report.h"
#include "timer.h"
#include <stdio.h>
#include "print.h"


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};
static uint8_t f22_tracker;
// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    _KC_DBG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_1,  KC_2  , KC_3,  KC_4
    ),
    [_FN] = LAYOUT(
        QMKBEST, QMKURL,  _______,_______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
                dprintf("writing to oled\n");
            } else { }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else { }
            break;
        case _KC_DBG:
            if (record->event.pressed) { SEND_STRING("Test"); } else {}
            break;
        case KC_A ... KC_F21: //notice how it skips over F22
        case KC_F23 ... KC_EXSEL: //exsel is the last one before the modifier keys
        if (record->event.pressed) {
            register_code(KC_F22); //this means to send F22 down
            f22_tracker++;
            register_code(keycode);
            return false;
        }
        break;

    }
    return true;

}
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A ... KC_F21: //notice how it skips over F22
        case KC_F23 ... KC_EXSEL: //exsel is the last one before the modifier keys
            if (!record->event.pressed) {
                f22_tracker--;
                if (!f22_tracker) {
                    unregister_code(KC_F22); //this means to send F22 up
                }
            }
            break;
    }
}

void tap_modified_key(uint16_t keycode,uint16_t modifier){
    register_code(modifier);
    tap_code_delay(keycode, 5);
    unregister_code(modifier);

}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    else if(index ==1 || index == 2 || index == 3){
        if (clockwise) {
            tap_modified_key(KC_A+(2*(index-1)),KC_F22);
        } else {
            tap_modified_key(KC_B+(2*(index-1)), KC_F22);
        }
    }
    return false;
}

