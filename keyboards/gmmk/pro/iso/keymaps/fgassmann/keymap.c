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
#include "rgb_matrix_map.h"
#include "keymap_german.h"

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
//Unicode
enum unicode_names {
    _oe,_OE, // ö Ö
    _ae,_AE, // ä Ä
    _ue,_UE, // ü Ü
    _sz,     // ß
    IRONY,
    SNEK
};
const uint32_t PROGMEM unicode_map[] = {
    [_oe] = 0xF6, [_OE] = 0xD6, // ö Ö
    [_ae] = 0xE4, [_AE] = 0xC4,
    [_ue] = 0xFC, [_UE] = 0xDC,
    [_sz] = 0xDF,
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};


enum custom_keycodes {
  //LATEX GREEK
    _TEX_A_= SAFE_RANGE,_TEX_a_, //Alpha 1.
    _TEX_B_, _TEX_b_,//Beta 2.
    _TEX_C_, _TEX_c_,//Psi 23.
    _TEX_D_, _TEX_d_,//Delta 4.
    _TEX_E_, _TEX_e_, //Epsilon, vareppsilon 5.
    _TEX_F_, _TEX_f_, //Phi 21.
    _TEX_G_, _TEX_g_, //Gamma 3.
    _TEX_H_, _TEX_h_, //Eta 7.
    _TEX_I_, _TEX_i_, //Iota 9.
    _TEX_J_, _TEX_j_, //XI 14.
    _TEX_K_, _TEX_k_, //Kappa 10.
    _TEX_L_, _TEX_l_, //Lambda 11.
    _TEX_M_, _TEX_m_, //Mu 12.
    _TEX_N_, _TEX_n_, //Nu 13.
    _TEX_O_, _TEX_o_, //Omicron 15.
    _TEX_P_, _TEX_p_, //Pi 16.
    _TEX_Q_, _TEX_q_, //???
    _TEX_R_, _TEX_r_, //Rho 17.
    _TEX_S_, _TEX_s_, //Sigma 18.
    _TEX_T_, _TEX_t_, //Tau 19.
    _TEX_U_, _TEX_u_, //Theta 8.
    _TEX_V_, _TEX_v_, //Omega 24.
    _TEX_W_, _TEX_w_, //
    _TEX_X_, _TEX_x_, //Chi 22.
    _TEX_Y_, _TEX_y_, //Upsilon 20.
    _TEX_Z_, _TEX_z_, //Zeta 6.
  //LATEX FUNCTIONS
  //Environments
    _BMAT,
    _MAT,
    _PMAT,
    _VMAT,
    _LCAS,
    _RCAS,
    //Spacing
    _TEX_SPACE,
    _TEX_QUAD,
    //Arrows
    _UP_AR,
    _LE_AR,
    _DN_AR,
    _RG_AR
};

static char *tex_greek_chars[] ={
  "Alpha","alpha","Beta","beta","Psi","psi","Delta","delta","Epsilon","varepsilon","Phi","phi","Gamma","gamma","Eta","eta",
  "Iota","iota","Xi","xi","Kappa","kappa","Lambda","lambda","Mu","mu","Nu","nu","Omicron","omicron","Pi","pi","x","x","Rho",
  "rho","Sigma","sigma","Tau","tau","Theta","theta","Omega","omega","x","x","Chi","chi","Upsilon","upsilon","Zeta","zeta"
};
static char *tex_functions[] ={
  //Spacing
  "\\space",
  "\\quad",
  //Single Arrows
  "uarr", 
  "larr",
  "darr",
  "rarr"
};
static char *tex_environments[] ={
  //Environments
  "bmatrix", // Matrix []
  "matrix",  // Matrix without brackets
  "pmatrix", // Matrix ()
  "vmatrix", // Matrix ||
  "cases",   // Cases  {
  "rcases"   // Cases  }
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //Greek chars
  if(keycode >= _TEX_A_ && keycode <= _TEX_z_){
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
//TODO Update this
//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
//      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐    ┌───────┐
 * │ESC│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  PRT  │    | MUTE  |
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───────┤    ├───────┤
 * │ ^ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ß │ ´ │  BSPC │    | TO(1) |
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤    ├───────┤
 * │ TAB │ Q │ W │ E │ R │ T │ Z │ U │ I │ O │ P │ Ü │ + │ ENT │    |       |
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │    ├───────┤
 * │ CAPS │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ # │    │    |       |
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┼────┼───────┤
 * │LSFT│ < │ Y │ X │ C │ V │ B │ N │ M │ , │ . │ - │   RSFT   │ UP |       |
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┼────┼───────┤
 * │LCTL│LGUI│LALT│           SPC          │RALT│APP │RCTL│LEFT│DOWN| RIGHT |
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┼────┼───────┘
 */


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TO(_TEX_ACTIVE),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   TO(_BASE_TEXT),
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_F13 , KC_ENT,           TO(_BASE_CODE),
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    //Latex
    //TODO more latex keybindings
    [_TEX_ACTIVE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   TO(_BASE_TEXT),
      TO(_TEX), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE_CODE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, MO(_KYBS),
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_TEX] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _TEX_q_, _TEX_w_, _TEX_e_, _TEX_r_, _TEX_t_, _TEX_y_, _TEX_u_, _TEX_i_, _TEX_o_, _TEX_p_, _BMAT,   _MAT,                   _______,
  TO(_TEX_ACTIVE),_TEX_a_,_TEX_s_, _TEX_d_, _TEX_f_, _TEX_g_, _TEX_h_, _TEX_j_, _TEX_k_, _TEX_l_, _______, _______, _______, _______,          _______,
    OSL(_TEXSH), _______, _TEX_z_, _TEX_x_, _TEX_c_, _TEX_v_, _TEX_b_, _TEX_n_, _TEX_m_, _______, _______, _______,          _______, _UP_AR,  _______,
        _______, _______, _______,                            _TEX_SPACE,                         _______, _______, _______, _LE_AR,  _DN_AR,  _RG_AR
    ),
    [_TEXSH] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _PMAT,   _VMAT  , _______, _______, _______,          _______,
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
  TO(_TEXT_DE), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_F13 , KC_ENT,           TO(_BASE_CODE),
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(_KYBS),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_TEXT_DE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          X(SNEK),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE),
        _______, _______, _______, _______, _______,_______,_______,XP(_ue,_UE),_______,XP(_oe,_OE),_______,_______,_______,                   TO(_BASE_TEXT),
  TO(_BASE_TEXT),XP(_ae,_AE),X(_sz),_______,_______,_______, _______, _______, _______, _______, _______, _______, _______, _______,          TO(_BASE_CODE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, MO(_KYBS),
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    //Coding
    // TODO camelcase on Caps
    [_BASE_CODE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TO(_TEX_ACTIVE),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   TO(_BASE_TEXT),
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_F13 , KC_ENT,           TO(_BASE),
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(_KYBS),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_KYBS] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______,   RESET,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   RESET,          TO(_BASE),
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
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
  
