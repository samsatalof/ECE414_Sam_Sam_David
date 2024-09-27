#include "ts_lcd.h"
#include "TFTMaster.h"
#include "TouchScreen.h"

bool get_ts_lcd(uint16_t *px, uint16_t *py) {

    struct TSPoint p;
    getPoint(&p);
    *px = (p.x * (ILI9340_TFTWIDTH))/(touchscrn_width);
    *py = (p.y * (ILI9340_TFTHEIGHT))/(touchscrn_height);

}

void ts_lcd_init() {
    stdio_init_all();
    tft_init_hw();
    tft_begin();
    tft_setRotation(0);
    tft_fillScreen(ILI9340_BLACK);
}