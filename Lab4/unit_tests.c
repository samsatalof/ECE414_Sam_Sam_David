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

    // Unit Test TX
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
}