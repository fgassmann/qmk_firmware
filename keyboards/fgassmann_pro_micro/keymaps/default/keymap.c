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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    _KC_DBG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_A,    _KC_DBG,    MO(_FN)
    ),
    [_FN] = LAYOUT(
        QMKBEST, QMKURL,  _______
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

            dprintf("changing light\n");
            i2c_status_t i2c_status = i2c_start(PCF8575_ADDR, I2C_TIMEOUT);

            if (i2c_status == I2C_STATUS_ERROR){dprintf("error init\n");}
            if (i2c_status == I2C_STATUS_TIMEOUT){dprintf("timeout init\n");}

            if (out_high){
                uint8_t all_low = 0;
                i2c_status = i2c_transmit(PCF8575_ADDR, &all_low, 1, I2C_TIMEOUT);
                out_high =false;
            }
            else{
                uint8_t all_high = 0b11111111;
                i2c_status = i2c_transmit(PCF8575_ADDR, &all_high, 1, I2C_TIMEOUT);
                out_high =true;
            }
            if (i2c_status == I2C_STATUS_ERROR){dprintf("error init\n");}
            if (i2c_status == I2C_STATUS_TIMEOUT){dprintf("timeout init\n");}

            i2c_stop();
            dprintf("Send to PCF8575 (%d) \n", i2c_status);


            } else {
                //scan_i2c();
            }

    }
    return true;

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
