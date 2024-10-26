
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A,    KC_B,    KC_C
    ),
    [1] = LAYOUT(
        KC_D, KC_E,   KC_F
    ),
    [2] = LAYOUT(
        KC_G, KC_H,  KC_I
    ),
    [3] = LAYOUT(
        KC_J, KC_K,  KC_L
    )
};
