 /* This program is free software: you can redistribute it and/or modify
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

#define KC_NUM_SPC LT(1, KC_SPC)
#define KC_GA LGUI_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_CD LCTL_T(KC_D)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_CK RCTL_T(KC_K)
#define KC_AL RALT_T(KC_L)
#define KC_GSCLN RGUI_T(KC_SCLN)

void oled_logo_task(void);
void oled_status_task(void);
void oled_matrix_task(void);
void oled_disabled_task(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,     KC_P,
    KC_GA,   KC_AS,   KC_CD,   KC_SF,   KC_G,    KC_H,    KC_SJ,    KC_CK,   KC_AL,    KC_ENT,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,     KC_M,    KC_COMM,  KC_DOT,
            KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, KC_NUM_SPC, KC_RALT, KC_RGUI, KC_RCTL,        KC_ESC
  ),
  [1] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_MINS,
    KC_LCBR, KC_LBRC, KC_LPRN, KC_UNDS, KC_NO,   KC_RPRN, KC_RBRC, KC_RCBR, KC_SCLN, KC_QUOTE,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS
  )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [1] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()){
        HSV layer_hsv = {rgb_matrix_get_hue(), ((int)rgb_matrix_get_sat()>>1)+128, rgb_matrix_get_val()}; //get the matrix hue, sat (minimum 50%), and value
        HSV mod_hsv = {rgb_matrix_get_hue(), ((int)rgb_matrix_get_sat()>>1)+128, rgb_matrix_get_val()};

        layer_hsv.h += 16*get_highest_layer(layer_state|default_layer_state); //hue-shift the layer indicator based on highest layer (of 0-15 layers)
        layer_hsv.h = layer_hsv.h % 256; //modulo 256

        int mods = get_mods() | get_oneshot_mods(); //get all modifiers, either held or OSM
        mods = ((mods>>4)|mods) & 0x0F;  //combine left and right mods, and take just the bottom 4 bits (0-15)

        mod_hsv.h += 16*mods; //hue-shift the modifier indicator based on the modifiers held (of 0-15 combinations)
        mod_hsv.h = mod_hsv.h % 256; //modulo 256

        if (host_keyboard_led_state().caps_lock) { //if capslock is active
            layer_hsv.s = 0; //turn both indicators white
            mod_hsv.s = 0;
        };

        RGB layer_rgb = hsv_to_rgb(layer_hsv);
        RGB mod_rgb = hsv_to_rgb(mod_hsv);
        rgb_matrix_set_color(0, layer_rgb.r, layer_rgb.g, layer_rgb.b);
        rgb_matrix_set_color(1, mod_rgb.r, mod_rgb.g, mod_rgb.b);
    }
	return true;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_task_user(void) {

    oled_set_brightness(rgb_matrix_get_speed());

    switch (via_get_layout_options()&0x03) {
        case 1:
            oled_logo_task();
            break;
        case 2:
            oled_status_task();
            break;
        case 3:
            oled_matrix_task();
            break;
        default:
            oled_disabled_task();
    }

    return false;
}

void oled_logo_task(void) {
    const unsigned char lasomme [] PROGMEM = {
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1f, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1f, 0x00, 0xf0, 0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 0x80, 0x80, 0x00, 0x40, 0x40, 0x01, 0xc0,
    0x1e, 0x03, 0xfc, 0x00, 0x01, 0xf8, 0x1f, 0x81, 0xc3, 0xe3, 0xe0, 0xe1, 0xf1, 0xf0, 0x07, 0xf0,
    0x3e, 0x07, 0xfc, 0x00, 0x01, 0xf0, 0x7f, 0xc1, 0xe7, 0xe7, 0xe0, 0xf3, 0xf3, 0xf0, 0x0f, 0xf0,
    0x3e, 0x0f, 0x8e, 0x00, 0x03, 0xf0, 0x7c, 0xe1, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf8, 0x1f, 0x30,
    0x3c, 0x1f, 0x06, 0x00, 0x03, 0xf0, 0xf9, 0xe1, 0xfd, 0xfd, 0xf0, 0xfe, 0xfe, 0xf8, 0x3e, 0x30,
    0x3c, 0x1e, 0x06, 0x00, 0x07, 0xe1, 0xf1, 0xf1, 0xf9, 0xf9, 0xe0, 0xfc, 0xfc, 0xf0, 0x7c, 0x30,
    0x7c, 0x3e, 0x0c, 0x00, 0x07, 0xe1, 0xe1, 0xb1, 0xf1, 0xf1, 0xe0, 0xf8, 0xf8, 0xf0, 0x7c, 0x70,
    0x78, 0x3c, 0x0e, 0x00, 0x07, 0xe1, 0xe1, 0x33, 0xf1, 0xf3, 0xe1, 0xf8, 0xf9, 0xf0, 0xf8, 0x60,
    0x78, 0x3c, 0x0f, 0x04, 0x0c, 0xf3, 0xe0, 0x33, 0xe3, 0xe3, 0xe1, 0xf1, 0xf1, 0xf0, 0xf8, 0xe3,
    0x78, 0x7c, 0x0f, 0x0e, 0x0c, 0xf3, 0xc0, 0x33, 0xc3, 0xc3, 0xc1, 0xe1, 0xe1, 0xe0, 0xf1, 0xc3,
    0x78, 0x78, 0x1f, 0x0c, 0x1e, 0xf3, 0xc0, 0x33, 0xc3, 0xc3, 0xc3, 0xe1, 0xe1, 0xe1, 0xf3, 0x86,
    0xf8, 0x78, 0x1f, 0x0c, 0x1e, 0xf3, 0xc0, 0x33, 0xc3, 0xc3, 0xc3, 0xe1, 0xe1, 0xe1, 0xff, 0x06,
    0xf0, 0xf8, 0x3f, 0x18, 0x3e, 0x73, 0xc0, 0x73, 0x83, 0x83, 0xc7, 0xe1, 0xe1, 0xe3, 0xfe, 0x0c,
    0xf1, 0xf8, 0x3e, 0x18, 0x38, 0x7b, 0xe0, 0x73, 0x83, 0x83, 0xc7, 0xc1, 0xc1, 0xe3, 0xf8, 0x1c,
    0xf1, 0xf8, 0x7e, 0x30, 0x38, 0x79, 0xe0, 0xe3, 0x83, 0x83, 0xcf, 0xc1, 0xc1, 0xe7, 0xf0, 0x18,
    0xf3, 0xfc, 0xfe, 0x70, 0x38, 0x79, 0xf1, 0xe3, 0x83, 0x83, 0xdf, 0xc1, 0xc1, 0xee, 0xf8, 0x38,
    0x7f, 0x3f, 0xdf, 0xe0, 0x1c, 0x78, 0xff, 0xc3, 0x83, 0x83, 0xf9, 0xc1, 0xc1, 0xfe, 0xfc, 0xf0,
    0x7e, 0x1f, 0x8f, 0xc0, 0x1f, 0xf0, 0x7f, 0x83, 0x83, 0x83, 0xf9, 0xc1, 0xc1, 0xfc, 0x7f, 0xe0,
    0x3c, 0x0f, 0x0f, 0x80, 0x07, 0xe0, 0x3f, 0x00, 0x80, 0x81, 0xf0, 0x40, 0x40, 0xf8, 0x3f, 0xc0,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    unsigned int x;
    unsigned int y;
    unsigned char bit;
    uint index = 0;
    for (y = 0; y < 32; y++){
        for (x = 0; x < 16; x++){
            for (bit = 0; bit < 8; bit++){
                oled_write_pixel(31-y, (8*x)+bit, lasomme[index]&(0x80>>bit));
            }
            index++;
        }
    }
}

void oled_status_task(void) {
    oled_write_pixel(31, 6, 0);
    oled_write_pixel(30, 5, 0);
    oled_write_pixel(30, 6, 0);
    oled_write_pixel(30, 7, 0);
    // Host Keyboard Layer Status
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR(" LYR \n"), false);
            break;
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        case 9: case 10: case 11: case 12: case 13: case 14: case 15:
            oled_write_P(PSTR(" "), true);
            oled_write_P(get_u8_str(get_highest_layer(layer_state), '0'), true);
            oled_write_P(PSTR(" \n"), true);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_P(PSTR(" LRX \n"), true);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR(" CAP \n"), led_state.caps_lock);
    oled_write_P(PSTR(" NUM \n"), led_state.num_lock);
    oled_write_P(PSTR(" SCL \n"), led_state.scroll_lock);

    //Host Keyboard Modifier Status
    int mods = get_mods() | get_oneshot_mods(); //get all modifiers, either held or OSM
    mods = ((mods>>4)|mods) & 0x0F;  //combine left and right mods, and take just the bottom 4 bits (0-15)
    oled_write_P(PSTR(" CTL \n"), mods & 0x1);
    oled_write_P(PSTR(" SFT \n"), mods & 0x2);
    oled_write_P(PSTR(" ALT \n"), mods & 0x4);
    oled_write_P(PSTR(" GUI \n"), mods & 0x8);
}

void oled_matrix_task(void) {
    oled_write_pixel(31, 6, 0);
    oled_write_pixel(30, 5, 0);
    oled_write_pixel(30, 6, 0);
    oled_write_pixel(30, 7, 0);

    int row;
    int col;
    for (row = 0; row < MATRIX_ROWS; row++) {
        oled_write_P(PSTR("-----"), false);

        for (col = 0; col < MATRIX_COLS; col++){
            if (matrix_get_row(row) & (1 << col)) {
                oled_write_char(col+48, false);
            } else {
                oled_write_P(PSTR(" "), false);
            }

        }

        oled_write_P(PSTR("-----"), false);
    }

}

void oled_disabled_task(void) {
    oled_write_pixel(31, 6, 0);
    oled_write_pixel(30, 5, 0);
    oled_write_pixel(30, 6, 0);
    oled_write_pixel(30, 7, 0);

    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
    oled_write_P(PSTR("     \n"), false);
}

#endif
