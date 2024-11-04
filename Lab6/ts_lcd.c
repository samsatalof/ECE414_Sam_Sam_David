#include "ts_lcd.h"
#include "pico/stdlib.h"
#include "TFTMaster.h"
#include "hardware/adc.h"

void ts_lcd_init()
{
    stdio_init_all();
    tft_init_hw();
    tft_begin();
    tft_setRotation(1);
    tft_fillScreen(ILI9340_BLACK);
    tft_setTextSize(2);
    tft_setTextColor2(ILI9340_MAGENTA, ILI9340_BLACK);
    tft_setCursor(10, 10);
}