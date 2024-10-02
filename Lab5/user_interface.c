#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>

void drawInterface() {
    ts_lcd_init();
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
    
}