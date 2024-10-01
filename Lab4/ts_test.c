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
uint8_t cnt;
uint32_t t1, t2;

enum Touch_STATES {
    check,
    nocheck
} Touch_STATE;

void tick_fct() {
    switch (Touch_STATE) {
        case check:
        Touch_STATE = nocheck;
        break;
        case nocheck:
        if (cnt>10) {
            Touch_STATE = check;
        }
    }

    switch (Touch_STATE){
        case check:
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
        break;
        case nocheck:
        break;
    }
}

int main()
{

    px = &x;
    py = &y;
    ts_lcd_init();
    
    /*
    t1 = timer_read();
    while (1)
    {

        t2 = timer_read();
        if (timer_elapsed_ms(t1, t2) >= 10)
        {
            tick_fct();
            t1 = t2;
        }
    } */
    

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