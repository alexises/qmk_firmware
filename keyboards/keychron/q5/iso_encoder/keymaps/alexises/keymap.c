/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
  BASE_LAYER,
  PGUP_LAYER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE_LAYER] = LAYOUT_iso_99(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,         KC_F11,   KC_F12,             KC_DEL,   KC_HOME,  KC_END,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,        KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,        KC_RBRC,                      KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,        KC_NUHS,  KC_ENT,             KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,        KC_RSFT,            KC_UP,    KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  TG(PGUP_LAYER), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT,  KC_PENT),
    [PGUP_LAYER] = LAYOUT_iso_99(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,                 KC_PSCR,  KC_PAUS,  KC_INS,  KC_F24,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,                KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,                          KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_NUHS,  KC_ENT,                 KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,    KC_RSFT,                KC_PGUP,  KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  TG(PGUP_LAYER), KC_RCTL,  KC_HOME,  KC_PGDN,  KC_END,   KC_P0,    KC_PDOT,  KC_PENT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE_LAYER] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [PGUP_LAYER] = {ENCODER_CCW_CW(KC_F23,  KC_F22) },
};
#endif

struct keycode_color {
    uint8_t layer;
    uint16_t keycode;
    uint8_t color[3];
};

struct keyidx_color {
    uint32_t pos;
    uint8_t color[3];
};

const struct keycode_color multilayer_config[] = {
    {.layer = BASE_LAYER,  .keycode = KC_UP    , .color = {0,   255, 0}},
    {.layer = BASE_LAYER,  .keycode = KC_DOWN  , .color = {255, 0  , 0}},
    {.layer = BASE_LAYER,  .keycode = 0        , .color = {255, 255, 255}},
    {.layer = PGUP_LAYER,  .keycode = KC_UP    , .color = {0,   0  , 255}},
    {.layer = PGUP_LAYER,  .keycode = KC_DOWN  , .color = {255, 0  , 0}},
    {.layer = PGUP_LAYER,  .keycode = 0        , .color = {255, 255, 0}}
};

#define LAYER_COUNT 2
#define MAX_KEY_CONFIG MATRIX_ROWS * MATRIX_COLS
struct keyidx_color key_config[LAYER_COUNT][MAX_KEY_CONFIG];

void set_layer_color(uint8_t l) {
    for (int i = 0; i < MAX_KEY_CONFIG; ++i) {
        rgb_matrix_set_color(i, key_config[l][i].color[0], key_config[l][i].color[1], key_config[l][i].color[2]);
    }
}

void keyboard_post_init_user(void) {
    // create mapping structure between RGB
    for (int l = 0; l < LAYER_COUNT; ++l) {
        // first find the default color
        uint8_t default_color[3] = {0, 0, 0};
        for (int p = 0; p < sizeof(multilayer_config); ++p) {
            if (multilayer_config[p].layer != l ||
                multilayer_config[p].keycode != 0) {
                continue;
            }
            default_color[0] = multilayer_config[p].color[0];
            default_color[1] = multilayer_config[p].color[1];
            default_color[2] = multilayer_config[p].color[2];
            break;
        }
        
        // next, fill up the matrix
        for (int y = 0; y < MATRIX_ROWS; ++y) {
            for (int x = 0; x < MATRIX_COLS; ++x) {
                bool keymap_found = false;
                for (int p = 0; p < sizeof(multilayer_config); ++p) {
                    if (keymaps[l][y][x] == multilayer_config[p].keycode) {
                        key_config[l][y * MATRIX_ROWS + x].color[0] = multilayer_config[p].color[0];
                        key_config[l][y * MATRIX_ROWS + x].color[1] = multilayer_config[p].color[1];
                        key_config[l][y * MATRIX_ROWS + x].color[2] = multilayer_config[p].color[2];
                        keymap_found = true;
                        break;
                    }
                }
                if (!keymap_found) {
                    key_config[l][y * MATRIX_ROWS + x].color[0] = default_color[0];
                    key_config[l][y * MATRIX_ROWS + x].color[1] = default_color[0];
                    key_config[l][y * MATRIX_ROWS + x].color[2] = default_color[0];
                }
            }
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t top_layer = get_highest_layer(state);
    set_layer_color(top_layer);
    return state;
}
