/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

enum layers {
    _BASE,
    _SECOND,
    _THIRD,
    _FOURTH
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_RBRC, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(_SECOND),  KC_SPC,     KC_ENT, MO(_THIRD), KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_SECOND] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_QUOT, KC_SCLN, KC_LBRC,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_NUBS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,     KC_ENT, MO(_FOURTH), KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_THIRD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_LEFT,  KC_DOWN, KC_UP, KC_RIGHT, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(_FOURTH),  KC_SPC,     KC_ENT, KC_TRNS, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_FOURTH] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_VOLU,                      KC_MPLY, KC_MRWD, KC_MFFD,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_NO,   KC_NO,   KC_NO,   KC_NO, LAG(KC_F), KC_VOLD,                  LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_UP), LCA(KC_RIGHT), LCAG(KC_LEFT), LCAG(KC_RIGHT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_MUTE,                      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_LGUI, KC_TRNS,  KC_SPC,      KC_ENT, KC_TRNS, KC_LALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        if (!is_keyboard_master()) {
            return OLED_ROTATION_0;
        }

        return rotation;
    }

    bool oled_task_user(void) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_P(PSTR("Base"), false);
                break;
            case _SECOND:
                oled_write_P(PSTR("Second"), false);
                break;
            case _THIRD:
                oled_write_P(PSTR("Third"), false);
                break;
            case _FOURTH:
                oled_write_P(PSTR("Fourth"), false);
                break;
            default:
                oled_write_P(PSTR("Undef"), false);
                break;
        }

        // Check and display modifier states
        uint8_t mods = get_mods();
        oled_write_P(PSTR("\nMods: "), false);
        if (mods) {
            if (mods & MOD_MASK_SHIFT) {
                oled_write_P(PSTR("Shift "), false);
            }
            if (mods & MOD_MASK_CTRL) {
                oled_write_P(PSTR("Ctrl "), false);
            }
            if (mods & MOD_MASK_ALT) {
                oled_write_P(PSTR("Alt "), false);
            }
            if (mods & MOD_MASK_GUI) {
                oled_write_P(PSTR("Cmd "), false);
            }
        }

        // Display WPM
        oled_write_P(PSTR("\nWPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);

        return false;
    }
#endif

