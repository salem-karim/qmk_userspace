/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include "bk_pointing_device.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    LAYER_NUMPAD,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
// #define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LO_DEL LT(LAYER_LOWER, KC_DEL)
#define RA_ENT LT(LAYER_RAISE, KC_ENT)
#define TO_BASE TO(LAYER_BASE)
#define NUMB MO(LAYER_NUMPAD)
#define PT_NUBS LT(LAYER_POINTER, KC_NUBS)
#define PT_DOT LT(LAYER_POINTER, KC_DOT)

#define CTL_QUOT MT(MOD_LCTL | MOD_RCTL, KC_QUOT)
#define SFT_SLSH MT(MOD_LSFT | MOD_RSFT, KC_SLSH)
#define SFT_NUHS MT(MOD_LSFT | MOD_RSFT, KC_NUHS)
#define CG_L C(G(KC_LEFT))
#define CG_R C(G(KC_RGHT))
#define LCA_A LCA(KC_A)
#define LCA_D LCA(KC_D)
#define LSA_A LSA(KC_A)
#define LSA_D LSA(KC_D)
#define CG_H C(G(KC_H))
#define CG_J C(G(KC_J))
#define CG_K C(G(KC_K))
#define CG_L2 C(G(KC_L))
#define LSG_H LSG(KC_H)
#define LSG_J LSG(KC_J)
#define LSG_K LSG(KC_K)
#define LSG_L LSG(KC_L)
#define RALT_RBRC RALT(KC_RBRC)
#define RALT_7 RALT(KC_7)
#define RALT_8 RALT(KC_8)
#define RALT_9 RALT(KC_9)
#define RALT_0 RALT(KC_0)
#define S_NUHS S(KC_NUHS)
#define S_SLSH S(KC_SLSH)
#define S_EQL S(KC_EQL)
#define WWWR KC_WWW_REFRESH
#define MS_1 QK_MOUSE_BUTTON_1
#define MS_2 QK_MOUSE_BUTTON_2
#define MS_3 QK_MOUSE_BUTTON_3
#define RGB_TOG_ QK_RGB_MATRIX_TOGGLE
#define RGB_SAD_ QK_RGB_MATRIX_HUE_DOWN
#define RGB_SAI_ QK_RGB_MATRIX_HUE_UP

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, CTL_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,   PT_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,    KC_N,    KC_M,  KC_COMM, PT_DOT,  SFT_SLSH,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_LALT, KC_SPC,  LO_DEL,    KC_BSPC,  KC_RALT,
                                           KC_LGUI,  NUMB,      RA_ENT
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8, KC_F9,    KC_F10, KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_GRV, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),    S_EQL,   CG_L,    CG_R,  _______, _______, KC_RBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, RALT_RBRC, S_NUHS, KC_UP, S_SLSH,   S_EQL,      _______, LSA_A,   LSA_D, SFT_NUHS, KC_EQL, SFT_NUHS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, S(KC_RBRC),  KC_INS,  LCA_A,   LCA_D, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                  _______, _______,             _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_ESC,  RALT_7,  RALT_8,  RALT_9,  RALT_0, XXXXXXX,    S(KC_6), KC_PSLS, S(KC_8), S(KC_9), S(KC_0), KC_RBRC,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,  CG_H,    CG_J,    CG_K,    CG_L2, XXXXXXX,     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,  KC_EQL, SFT_NUHS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______,  LSG_H,   LSG_J,   LSG_K,   LSG_L, XXXXXXX,     KC_HOME, KC_END, KC_PGUP, KC_PGDN, _______,   _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,    KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU, KC_BRID,  WWWR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        _______, _______, RGB_TOG_, RGB_SAD_, DPI_RMOD, S_D_RMOD, S_D_MOD, DPI_MOD, RGB_SAI_, RGB_TOG_, KC_VOLD, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, MS_3,      MS_3,   KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        _______, _______, DRGSCRL, SNIPING, MS_1,    MS_2,      MS_1,   MS_2,    DRGSCRL, SNIPING, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                 _______, _______, _______,     _______, _______,
                                          _______, _______,     _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NUMPAD] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, KC_NUM,     KC_P7, KC_P8,   KC_P9, KC_PSLS,     _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______,    KC_P4, KC_P5,   KC_P6, KC_PAST,     _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, _______,    KC_P1, KC_P2,   KC_P3, KC_PMNS,     _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, G(KC_MUTE), KC_P0, KC_PDOT, KC_PENT, KC_PPLS,   _______, _______, _______, _______, _______, _______,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (!bkpd_get_pointer_sniping_enabled()) {
        int8_t deadzone = 2;

        if (mouse_report.x > -deadzone && mouse_report.x < deadzone) {
            mouse_report.x = 0;
        }

        if (mouse_report.y > -deadzone && mouse_report.y < deadzone) {
            mouse_report.y = 0;
        }
    }

    return mouse_report;
}
