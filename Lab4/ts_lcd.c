#include "ts_lcd.h"

bool get_ts_lcd(uint16_t *px, uint16_t *py) {

    

}

void ts_lcd_init() {
    stdio_init_all();
    tft_init_hw();
    tft_begin();
    tft_setRotation(0);
    tft_fillScreen(ILI9340_BLACK);
}