/*
    LCD init function

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

// Initializes and configures everything necessary to read touchscreen
void ts_lcd_init();

#endif