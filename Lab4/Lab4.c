#include "ts_lcd.h"
#include "TFTMaster.h"

uint16_t *px, *py;

int main()
{
    ts_lcd_init();
    //char buff[16];
    while (1)
    {
        if (get_ts_lcd(px, py))
        {
            tft_fillScreen(ILI9340_BLACK);
            tft_drawLine(*px - 5, *py, *px + 5, *py, ILI9340_YELLOW);
            tft_drawLine(*px, *py - 5, *px, *py + 5, ILI9340_YELLOW);
        }
        else
        {
            tft_setCursor(10, 10);
            tft_writeString("Last location pressed was: ");
            tft_writeString(*px);

            printf("Last location pressed was: %d, %d", *px, *py);
        }
    }
}