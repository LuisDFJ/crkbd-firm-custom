#pragma once

#include <stdint.h>
#include "keymap/keycodes.h"
#include "PIN_CFG.h"

#define LAYOUT_crkbd( \
        L16, L15, L14, L13, L12, L11, R11, R12, R13, R14, R15, R16, \
        L26, L25, L24, L23, L22, L21, R21, R22, R23, R24, R25, R26, \
        L36, L35, L34, L33, L32, L31, R31, R32, R33, R34, R35, R36, \
                  L43, L42, L41, R41, R42, R43 ) \
        { \
        [0] = { { L11,L12,L13,L14,L15,L16 },    \
                { L21,L22,L23,L24,L25,L26 },    \
                { L31,L32,L33,L34,L35,L36 },    \
                { L41,L42,L43,XXXXXXX,XXXXXXX,XXXXXXX} },  \
        [1] = { { R11,R12,R13,R14,R15,R16 },    \
                { R21,R22,R23,R24,R25,R26 },    \
                { R31,R32,R33,R34,R35,R36 },    \
                { R41,R42,R43,XXXXXXX,XXXXXXX,XXXXXXX} }  \
        } \

const uint8_t keymaps[][2][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_crkbd(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LAY2,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                                          KC_LALT, KC_LAY1,  KC_SPC,    KC_RGUI, KC_RSFT, KC_RCTL
  ),
    [1] = LAYOUT_crkbd(
      _______,  KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, _______,
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
      _______, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, _______, _______, _______, _______,
                                          _______, _______, _______,    _______, _______, _______
  ),
    [2] = LAYOUT_crkbd(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME,
      XXXXXXX, XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
      _______, XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                      KC_PGDN,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_END,
                                          _______, _______, _______,    _______, _______, _______
  ),
    //[3] = LAYOUT_split_3x6_3(
      //XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MRWD,
      //XXXXXXX, XXXXXXX, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU,                      XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX,
      //_______, XXXXXXX, RM_NEXT, RM_HUED, RM_SATD, RM_VALD,                      KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY,
                                          //XXXXXXX, _______, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
  //)
};
