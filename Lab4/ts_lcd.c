#include "ts_lcd.h"
#include "pico/stdlib.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "hardware/adc.h"

bool get_ts_lcd(uint16_t *px, uint16_t *py)
{

    struct TSPoint p;
    getPoint(&p);
    if (!(p.z < 20000))
    {
        return false;
    }
    else
    {
        *px = (p.x * (ILI9340_TFTWIDTH)) / (touchscrn_width);
        *py = (p.y * (ILI9340_TFTHEIGHT)) / (touchscrn_height);
        return true;
    }
}

void ts_lcd_init()
{
    stdio_init_all();
    adc_init();
    tft_init_hw();
    tft_begin();
    tft_setRotation(0);
    tft_fillScreen(ILI9340_BLACK);
    tft_setTextSize(1);
    tft_setTextColor2(ILI9340_MAGENTA,ILI9340_BLACK);
    tft_setCursor(10,10);
}