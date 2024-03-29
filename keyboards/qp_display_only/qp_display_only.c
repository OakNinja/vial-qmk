// Copyright 2023 OakNinja (@oakninja)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "qp_comms.h"

#ifdef GC_9A01
#include "qp_gc9a01_opcodes.h"
#include "gfx/cat240x240.qgf.h"
#else
#include "qp_st77xx_opcodes.h"
#include "gfx/cat320x240.qgf.h"
#endif


#include "color.h"
#include "config.h"

painter_device_t lcd;

void keyboard_post_init_kb(void) {
    //Display timeout
    wait_ms(LCD_WAIT_TIME);

    #ifdef GC_9A01
    lcd = qp_gc9a01_make_spi_device(LCD_HEIGHT, LCD_WIDTH, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, SPI_MODE);
    #else
    lcd = qp_st7789_make_spi_device(LCD_HEIGHT, LCD_WIDTH, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, SPI_MODE);
    #endif
    qp_init(lcd, LCD_ROTATION);

    // Some screens have inverted colors
    #ifdef LCD_INVERT_COLOR
    qp_comms_start(lcd);
    qp_comms_command(lcd, ST77XX_CMD_INVERT_ON);
    qp_comms_stop(lcd);
    #endif

    // Display offset
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);

    // Power on display, fill with white
    qp_power(lcd, 1);
    qp_rect(lcd, 0, 0, LCD_HEIGHT, LCD_WIDTH, HSV_WHITE, 1);

    // Paint catpaste/Katten Paste
    painter_image_handle_t logo_image = qp_load_image_mem(gfx_cat);
    qp_drawimage(lcd, 0, 0, logo_image);

    keyboard_post_init_user();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lights handling:
//  - Turn off backlight (screen) after timeout or suspend
//  - Turn off rgblight after timeout or suspend

// bool lights_off = false;

// __attribute__((weak)) void lights_wakeup_user(void) {};
// __attribute__((weak)) void lights_suspend_user(void) {};

//void backlight_wakeup(void) {
//    backlight_set(BACKLIGHT_DEFAULT_LEVEL);
//}

// void backlight_suspend(void) {
//     backlight_set(0);
// }

// void lights_wakeup(void) {
//     lights_off = false;
//     rgblight_wakeup();
//     backlight_wakeup();
//     lights_wakeup_user();
// }

// void lights_suspend(void) {
//     lights_off = true;
//     lights_suspend_user();
//     rgblight_suspend();
//     backlight_suspend();
// }

// void housekeeping_task_kb(void) {
//     if ( lights_off && last_input_activity_elapsed() <= LIGHTS_TIMEOUT)
//     {
//         lights_wakeup();
//     }
//     if (!lights_off && last_input_activity_elapsed() > LIGHTS_TIMEOUT) {
//         lights_suspend();
//     }
// }

//void suspend_power_down_kb(void) {
//    //lights_suspend();
//    qp_power(lcd, true);
//    backlight_wakeup();
//    //suspend_power_down_user();
//}
//
//void suspend_wakeup_init_kb(void) {
//    qp_power(lcd, true);
//    backlight_wakeup();
//    //lights_wakeup();
//    //suspend_wakeup_init_user();
//}
