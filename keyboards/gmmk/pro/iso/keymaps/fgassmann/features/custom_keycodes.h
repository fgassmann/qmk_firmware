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

//Unicode for entering german characters on an englisch layout
enum unicode_names {
    _oe,_OE, // ö Ö
    _ae,_AE, // ä Ä
    _ue,_UE, // ü Ü
    _sz,_EU,  // ß €
    //I left these in just for fun
    IRONY,
    SNEK
};

const uint32_t PROGMEM unicode_map[] = {
    [_oe] = 0xF6, [_OE] = 0xD6,  // ö Ö
    [_ae] = 0xE4, [_AE] = 0xC4,  // ä Ä
    [_ue] = 0xFC, [_UE] = 0xDC,  // ü Ü
    [_sz] = 0xDF, [_EU] = 0x20AC, // ß €
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};

// NOTE: making the characters Unicode symbols instead of macros would probably have been more elegant, however not all Latex editors support this,
// also the order matters
enum custom_keycodes {
  _SNAKECASE = SAFE_RANGE,
  _CAMELCASE,

  //LATEX GREEK
    _TEX_A_,_TEX_a_, //Alpha
    _TEX_B_, _TEX_b_,//Beta
    _TEX_C_, _TEX_c_,//Psi
    _TEX_D_, _TEX_d_,//Delta
    _TEX_E_, _TEX_e_, //Epsilon, vareppsilon
    _TEX_F_, _TEX_f_, //Phi
    _TEX_G_, _TEX_g_, //Gamma
    _TEX_H_, _TEX_h_, //Eta
    _TEX_I_, _TEX_i_, //Iota
    _TEX_J_, _TEX_j_, //XI
    _TEX_K_, _TEX_k_, //Kappa
    _TEX_L_, _TEX_l_, //Lambda
    _TEX_M_, _TEX_m_, //Mu
    _TEX_N_, _TEX_n_, //Nu
    _TEX_O_, _TEX_o_, //Omicron
    _TEX_P_, _TEX_p_, //Pi
    // Q ,q
    _TEX_R_, _TEX_r_, //Rho
    _TEX_S_, _TEX_s_, //Sigma
    _TEX_T_, _TEX_t_, //Tau
    _TEX_U_, _TEX_u_, //Theta
    _TEX_V_, _TEX_v_, //Omega
    _TEX_W_, _TEX_w_, // ??
    _TEX_X_, _TEX_x_, //Chi
    _TEX_Y_, _TEX_y_, //Upsilon
    _TEX_Z_, _TEX_z_, //Zeta
  //LATEX Environments
    _BMAT,
    _MAT,
    _PMAT,
    _VMAT,
    _LCAS,
    _RCAS,
  //LATEX FUNCTIONS
    //Spacing
    _TEX_SPACE,
    _TEX_QUAD,
    _TEX_ENT,
    //Misc
    _TEX_Q_, _TEX_q_, // ?? , text
    _TEX_EQ,
    _TEX_FR,
    _TEX_OB,_TEX_UB,
    //Arrows
    _UP_AR,
    _LE_AR,
    _DN_AR,
    _RG_AR
};

static char *tex_greek_chars[] ={
  "Alpha","alpha","Beta","beta","Psi","psi","Delta","delta","Epsilon","varepsilon","Phi","phi","Gamma","gamma","Eta","eta",
  "Iota","iota","Xi","xi","Kappa","kappa","Lambda","lambda","Mu","mu","Nu","nu","Omicron","omicron","Pi","pi","Rho",
  "rho","Sigma","sigma","Tau","tau","Theta","theta","Omega","omega","x","x","Chi","chi","Upsilon","upsilon","Zeta","zeta"
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

static char *tex_functions[] ={
  //Spacing
  "space",
  "quad",
  "\\",
  //Misc
  "","text{}", 
  "stackrel{!}{=}",
  "frac{a}{b}",
  "overbrace{}^{\\text{}}","underbrace{}^{\\text{}}",
  //Single Arrows
  "uarr", 
  "larr",
  "darr",
  "rarr"
};
