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

    // Unit Test T3
    // while(1) {
    //     if (get_ts_lcd(px, py))
    //     {
    //         if ((px != NULL) && (py != NULL))
    //         {
    //             tft_fillScreen(ILI9340_MAGENTA);
    //         } else {
    //             tft_fillScreen(ILI9340_BLACK);
    //         }
    //     } else {
    //         tft_fillScreen(ILI9340_BLUE);
    //     }
    // }

    // Unit Test T4
    // while (1)
    // {
    //     sprintf(buf, "Hello World!");
    //     tft_setCursor(10, 10);
    //     tft_writeString(buf);
    // }

    // Unit Test T5 was iteratively improved, and is now just ts_test
    // Here's our earlier version that we used to calibrate the linear interpolation:
    // while(1) {
    //     if (get_ts_lcd(px, py))
    //     {
    //         if ((px != NULL) && (py != NULL))
    //         {
    //             tft_fillScreen(ILI9340_BLACK);
    //             sprintf(buf, "Last location pressed was: %d, %d", *px, *py);
    //             tft_setCursor(10, 10);
    //             tft_writeString(buf);
    //         }
    //     }
    //     else
    //     {
    //         tft_fillScreen(ILI9340_BLACK);
    //         sprintf(buf, "Last location pressed was: %d, %d", *px, *py);
    //         tft_setCursor(10, 10);
    //         tft_writeString(buf);
    //     }
    // }
}