/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "features/custom_keycodes.h"
#include "features/rgb_matrix_map.h"
#include "features/casemodes.h"

//Layers
enum custom_layers {
  _BASE =0, // default layer
  _TEX_ACTIVE, // latex ready
  _TEX, // latex active
  _TEXSH,// latex active and shifted
  _BASE_TEXT,
  _TEXT_DE,
  _BASE_CODE,
  _MDIA, // media keys not used
  _KYBS // Keyboard settings

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //Greek chars
  if (!process_case_modes(keycode, record)) {
        return false;
  }
  else if(keycode == _SNAKECASE){
    if (record->event.pressed) {
      enable_xcase_with(KC_UNDS);
    }
    return false;
  }
   else if(keycode == _CAMELCASE){
    if (record->event.pressed) {
      enable_xcase_with(OSM(MOD_LSFT));
    }
    return false;
  }
  else if(keycode >= _TEX_A_ && keycode <= _TEX_z_){
    if (record->event.pressed) {SEND_STRING("\\");SEND_STRING(tex_greek_chars[keycode - _TEX_A_]);SEND_STRING(" "); }
  }
  //Latex Environments
  else if (keycode >= _BMAT && keycode <= _RCAS){
    if (record->event.pressed) {
      SEND_STRING("\\begin{");SEND_STRING(tex_environments[keycode - _BMAT]);SEND_STRING("}");
      SEND_STRING("\\end{");SEND_STRING(tex_environments[keycode - _BMAT]);SEND_STRING("}");
      //Move 5 words left
      tap_code16(C(KC_LEFT));tap_code16(C(KC_LEFT));tap_code16(C(KC_LEFT));
      tap_code16(C(KC_LEFT));tap_code16(KC_LEFT);
      }
  }
  //Latex Functions
  else if (keycode >= _TEX_SPACE && keycode <= _RG_AR){
    if (record->event.pressed) {SEND_STRING("\\");SEND_STRING(tex_functions[keycode - _TEX_SPACE]);SEND_STRING(" ");}
  }
  else{
  }
  return true;
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TO(_TEX_ACTIVE),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   TO(_BASE_TEXT),
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_HASH, KC_ENT,           TO(_BASE_CODE),
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    //Latex
    [_TEX_ACTIVE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   TO(_BASE_TEXT),
        TO(_TEX),_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE_CODE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, MO(_KYBS),
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_TEX] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _TEX_UB, _______, _______, _______, _______, _______, _TEX_EQ, _______,          _______,
        KC_AMPR,  _TEX_q_, _TEX_w_, _TEX_e_, _TEX_r_, _TEX_t_, _TEX_y_, _TEX_u_, _TEX_i_, _TEX_o_, _TEX_p_, _BMAT,   _MAT,                   _______,
  TO(_TEX_ACTIVE),_TEX_a_,_TEX_s_, _TEX_d_, _TEX_f_, _TEX_g_, _TEX_h_, _TEX_j_, _TEX_k_, _TEX_l_, _______, _______, _______, _TEX_ENT,         _______,
    OSL(_TEXSH), _______, _TEX_z_, _TEX_x_, _TEX_c_, _TEX_v_, _TEX_b_, _TEX_n_, _TEX_m_, _______, _______, _TEX_FR,          _______, _UP_AR,  _______,
        _______, _______, _______,                            _TEX_SPACE,                         _______, _______, _______, _LE_AR,  _DN_AR,  _RG_AR
    ),
    [_TEXSH] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _TEX_OB, _______, _______, _PMAT,   _VMAT  , _______, _______, _______,          _______,
        _______, _TEX_Q_, _TEX_W_, _TEX_E_, _TEX_R_, _TEX_T_, _TEX_Y_, _TEX_U_, _TEX_I_, _TEX_O_, _TEX_P_, _LCAS,   _RCAS,                   _______,
        _______, _TEX_A_, _TEX_S_, _TEX_D_, _TEX_F_, _TEX_G_, _TEX_H_, _TEX_J_, _TEX_K_, _TEX_L_, _______, _______, _______, _______,          _______,
        TO(_TEX),_______, _TEX_Z_, _TEX_X_, _TEX_C_, _TEX_V_, _TEX_B_, _TEX_N_, _TEX_M_, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _TEX_QUAD,                          _______, _______, _______, _______, _______, _______
    ),
    //Text input
    [_BASE_TEXT] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TO(_TEX_ACTIVE),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   TO(_BASE),
    TO(_TEXT_DE),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_HASH, KC_ENT,           TO(_BASE_CODE),
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(_KYBS),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_TEXT_DE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          X(SNEK),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE),
        _______, _______, _______, X(_EU),  _______,_______,_______,XP(_ue,_UE),_______,XP(_oe,_OE),_______,_______,_______,                   TO(_BASE_TEXT),
  TO(_BASE_TEXT),XP(_ae,_AE),X(_sz),_______,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE_CODE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, MO(_KYBS),
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    //Settings
    [_KYBS] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______,   RESET,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, UC_M_LN, _______, _______, _______, _______,          _______,
        _______, _______, _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, UC_M_WC, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
    //Coding
    [_BASE_CODE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TO(_TEX_ACTIVE),
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   TO(_BASE_TEXT),
     _SNAKECASE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_HASH, KC_ENT,           TO(_BASE),
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   _CAMELCASE,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    


};
// clang-format on

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  switch(biton32(layer_state)) {
    //scroll through words
    case _BASE_TEXT:
    case _TEXT_DE:
    case _TEX_ACTIVE:
    case _TEX:
    case _TEXSH:
      if (clockwise) {
        tap_code16(C(KC_RGHT));
      } else {
        tap_code16(C(KC_LEFT));
      }
    break;
    case _BASE_CODE:
    //may need to change these depending on language
      if (clockwise) {
        tap_code16(C(KC_Y));
      } else {
        tap_code16(C(KC_Z));
      }
    break;
    //Controls Volume by default
    default:
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
      break;
  }
  return true;
}
#endif

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);

    #endif
}
void _change_indicators(int r,int b, int g){
  for (uint8_t i=0; i<LED_LIST_UTIL_CLUSTER_SIZE; i++) {
        rgb_matrix_set_color(LED_LIST_UTIL_CLUSTER[i], r,b,g);
      }
      for (uint8_t i=0; i<LED_SIDE_SIZE; i++) {
        rgb_matrix_set_color(LED_SIDE_LEFT[i], r,b,g);
        rgb_matrix_set_color(LED_SIDE_RIGHT[i], r,b,g);
      }

}

void rgb_matrix_indicators_user(void) {
  switch(biton32(layer_state)) {
    case _BASE:
      break;
    //TEXT
    case _BASE_TEXT:
      _change_indicators(0,0,80);
    break;
    case _TEXT_DE:
      _change_indicators(20,0,120);
    break;
    case _BASE_CODE:
      _change_indicators(65,0,65);
    break;
    //LATEX
    case _TEX_ACTIVE:
      _change_indicators(0,80,0);
    break;
    case _TEX:
      _change_indicators(0,100,25);
      break;
    //LATEX SHIFT
    case _TEXSH:
      _change_indicators(0,130,90);
      break;
    // KEYBOARD SETTINGS
    case _KYBS:
      rgb_matrix_set_color_all(RGB_RED);
      break;
    //
    default:
      break;
  }
}
  
