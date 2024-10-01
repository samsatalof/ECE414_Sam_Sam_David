#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>
#include "timer.h"

uint16_t *px, *py;
char buf[31];
uint16_t x, y;

int main()
{

    px = &x;
    py = &y;
    ts_lcd_init();
    

    while(1) {
        if (get_ts_lcd(px, py))
        {
            if ((px != NULL) && (py != NULL))
            {
                tft_fillScreen(ILI9340_BLACK);
                tft_drawLine(*px - 5, *py, *px + 5, *py, ILI9340_YELLOW);
                tft_drawLine(*px, *py - 5, *px, *py + 5, ILI9340_YELLOW);
                sprintf(buf, "Last location pressed was: %d, %d", *px, *py);
                tft_setCursor(10, 10);
                tft_writeString(buf);
            }
        }
        else
        {
            tft_fillScreen(ILI9340_BLACK);
            tft_drawLine(*px - 5, *py, *px + 5, *py, ILI9340_YELLOW);
            tft_drawLine(*px, *py - 5, *px, *py + 5, ILI9340_YELLOW);
            sprintf(buf, "Last location pressed was: %d, %d", *px, *py);
            tft_setCursor(10, 10);
            tft_writeString(buf);
        }
        sleep_ms(300);

    }

    /*
    while(1) {
        if (get_ts_lcd(px, py))
        {
            if ((px != NULL) && (py != NULL))
            {
                tft_fillScreen(ILI9340_MAGENTA);
            } else {
                tft_fillScreen(ILI9340_BLACK);
            }
        } else {
            tft_fillScreen(ILI9340_BLUE);
        }
    } */ 
   //UNIT TEST!!!!!!!
}