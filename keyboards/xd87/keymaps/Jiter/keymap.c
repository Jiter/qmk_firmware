/* Copyright 2018 Alexander Fougner <fougner89 at gmail.com>
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
#include "jiter.h"

#define _BL 0 // BaseLayer
#define _NL 1 // Neo2Layer

#define _FL 3 // FunctionLayer

#define _TL 5 // TransparentLayer as Template

/*
Keycount per Row
Keys 1 - 16
Keys 2 - 17
Keys 3 - 17
Keys 4 - 13
Keys 5 - 13
Keys 6 - 12
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //BaseLayer
  [_BL] = LAYOUT_tkl_ansisplit(\
      KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,            KC_PSCR, KC_SLCK, KC_PAUS, \
      DE_CIRC,DE_1,   DE_2,   DE_3,   DE_4,   DE_5,   DE_6,   DE_7,   DE_8,   DE_9,   DE_0,   DE_SS,  DE_ACUT,KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
      KC_TAB, DE_Q,   DE_W,   DE_E,   DE_R,   DE_T,   DE_Z,   DE_U,   DE_I,   DE_O,   DE_P,   DE_UDIA,DE_PLUS,DE_HASH,   KC_DEL,  KC_END,  KC_PGDN, \
      KC_CAPS,DE_A,   DE_S,   DE_D,   DE_F,   DE_G,   DE_H,   DE_J,   DE_K,   DE_L,   DE_ODIA,DE_ADIA,        KC_ENT, \
      CU_LSFT,DE_Y,   DE_X,   DE_C,   DE_V,   DE_B,   DE_N,   DE_M,   DE_COMM,DE_DOT, DE_MINS,                CU_RSFT,            KC_UP, \
      KC_LCTL,KC_LGUI,KC_LALT,        KC_SPC,         KC_SPC,                         KC_RALT,KC_RGUI,MO(_FL),KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT  ),
  //Neo2Layer
  [_NL] = LAYOUT_tkl_ansisplit(\
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, \
      DE_CIRC,DE_1,   NEO_2,  DE_3,   DE_4,   DE_5,   DE_6,   DE_7,   DE_8,   DE_9,   DE_0,   DE_MINS,DE_GRV ,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,DE_X,   DE_V,   DE_L,   DE_C,   DE_W,   DE_K,   DE_H,   DE_G,   DE_F,   DE_Q,   DE_SS,  DE_ACUT,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,DE_U,   DE_I,   DE_A,   DE_E,   DE_O,   DE_S,   DE_N,   DE_R,   DE_T,   DE_D,   DE_Y,           KC_TRNS, \
      KC_TRNS,        DE_UDIA,DE_ODIA,DE_ADIA,DE_P,   DE_Z,   DE_B,   DE_M,   DE_COMM,DE_DOT, DE_J,           KC_TRNS,            KC_TRNS,\
      KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS,         KC_TRNS,                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS  ),
  //FunctionLayer
  [_FL] = LAYOUT_tkl_ansisplit(\
      KC_TRNS,        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,DF(_BL),DF(_NL),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   RGB_TOG, KC_TRNS, KC_TRNS, \
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS, \
      KC_TRNS,        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,MY_PASS,        KC_TRNS,            KC_TRNS,\
      KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS,         KC_TRNS,                       KC_TRNS,KC_TRNS,KC_TRNS,RESET,     KC_TRNS, KC_TRNS, KC_TRNS  ),

  [_TL] = LAYOUT_tkl_ansisplit(\
      KC_TRNS,        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS, \
      KC_TRNS,        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS,            KC_TRNS,\
      KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS,         KC_TRNS,                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS  )
};



//  return true;
//}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  rgb_change_color(HSV_GREEN);

}
