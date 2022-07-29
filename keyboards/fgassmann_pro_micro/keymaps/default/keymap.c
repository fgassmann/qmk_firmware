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
#include "i2c_master.h"

#define PCF8575_ADDR (0x20 << 1)
#define I2C_TIMEOUT 100
bool out_high = false;

void scan_i2c(void){
    uint8_t address;
    
    dprintf("Scanning...\n\n");
    
    for(address = 1; address < 127; address++ )
    {
        i2c_status_t i2c_status = i2c_start(address << 1, I2C_TIMEOUT);
        if (i2c_status == I2C_STATUS_SUCCESS){
            dprintf("device found at %X\n\n",address);

        }
        else{
            dprintf("nothing at (%X)\n",address);
        }
        i2c_stop();
    }    
    dprintf("done\n");
}

//Not joytick



void matrix_init_kb(void) {
    i2c_init();

    // timer_init();
    // xOrigin = analogReadPin(xPin);
    // dprintf("analog read: Xorigin is %d))\n", xOrigin);
    // yOrigin = analogReadPin(yPin);
    // dprintf("analog read: Yorigin is %d))\n", yOrigin);
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
}


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
        KC_A,  KC_B  ,_KC_DBG,    MO(_FN)
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
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
        case _KC_DBG:
            if (record->event.pressed) {

                scan_i2c();

            } else {}
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

#ifdef OLED_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    //dprintf("writing to oled\n");

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }



}
#endif