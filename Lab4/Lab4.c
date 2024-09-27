#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>

uint16_t *px, *py;
char buf [31];
int main()
{
    ts_lcd_init();
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
            sprintf(buf, "Last location pressed was: %d, %d", *px, *py);
            tft_writeString(buf);
        }
    }
}