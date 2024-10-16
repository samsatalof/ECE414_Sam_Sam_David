#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>

struct buttonPressed
{
    bool depressed;
    char which_one;
} depressed, which_one;

void drawInterface()
{
    char buf[2];
    buf[1] = '\0';
    ts_lcd_init();

    // Buttons:
    // Column 1:
    tft_drawRoundRect(4, 40, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(4, 90, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(4, 140, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(4, 190, 75, 45, 60, ILI9340_WHITE);
    // Column 2:
    tft_drawRoundRect(83, 40, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(83, 90, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(83, 140, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(83, 190, 75, 45, 60, ILI9340_RED);
    // Column 3:
    tft_drawRoundRect(162, 40, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(162, 90, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(162, 140, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(162, 190, 75, 45, 60, ILI9340_BLUE);
    // Column 4:
    tft_drawRoundRect(241, 40, 75, 45, 60, ILI9340_YELLOW);
    tft_drawRoundRect(241, 90, 75, 45, 60, ILI9340_YELLOW);
    tft_drawRoundRect(241, 140, 75, 45, 60, ILI9340_YELLOW);
    tft_drawRoundRect(241, 190, 75, 45, 60, ILI9340_YELLOW);

    // Nums:
    // Column 1:
    buf[0] = '7';
    tft_setCursor(34, 62);
    tft_writeString(buf);
    buf[0] = '4';
    tft_setCursor(34, 107);
    tft_writeString(buf);
    buf[0] = '1';
    tft_setCursor(34, 152);
    tft_writeString(buf);
    buf[0] = '0';
    tft_setCursor(34, 197);
    tft_writeString(buf);
    // Column 2:
    buf[0] = '8';
    tft_setCursor(109, 62);
    tft_writeString(buf);
    buf[0] = '5';
    tft_setCursor(109, 107);
    tft_writeString(buf);
    buf[0] = '2';
    tft_setCursor(109, 152);
    tft_writeString(buf);
    buf[0] = 'C';
    tft_setCursor(109, 197);
    tft_writeString(buf);
    // Column 3:
    buf[0] = '9';
    tft_setCursor(184, 62);
    tft_writeString(buf);
    buf[0] = '6';
    tft_setCursor(184, 107);
    tft_writeString(buf);
    buf[0] = '3';
    tft_setCursor(184, 152);
    tft_writeString(buf);
    buf[0] = '=';
    tft_setCursor(184, 197);
    tft_writeString(buf);
    // Column 4:
    buf[0] = '+';
    tft_setCursor(259, 62);
    tft_writeString(buf);
    buf[0] = '-';
    tft_setCursor(259, 107);
    tft_writeString(buf);
    buf[0] = 'X';
    tft_setCursor(259, 152);
    tft_writeString(buf);
    buf[0] = '/';
    tft_setCursor(259, 197);
    tft_writeString(buf);
}

struct getButton()
{
    
}