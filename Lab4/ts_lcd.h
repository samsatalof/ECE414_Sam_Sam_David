/*
    Touchscreen driver that translates touchscreen raw data into LCD screen coordinates

    Authors: Sam Owens, David Green, Sam Satalof
*/

#ifndef TS_LCD_H
#define TS_LCD_H

#include <stdbool.h>
#include <inttypes.h>

#define CLK_GPIO 17
#define MOSI_GPIO 19
#define CS_GPIO 18
#define DC_GPIO 16
#define RST_GPIO 20
#define Xpos_GPIO 22
#define Xneg_GPIO 26
#define Ypos_GPIO 27
#define Yneg_GPIO 21
#define touchscrn_width 4200
#define touchscrn_height 4100

// Reads the status of touchscreen, returning true when a finger/stylus is placed on display,
// Two pointers are then assigned current finger/stylus position in LCD coordinates
bool get_ts_lcd(uint16_t *px, uint16_t *py);

// Initializes and configures everything necessary to read touchscreen
void ts_lcd_init();

#endif