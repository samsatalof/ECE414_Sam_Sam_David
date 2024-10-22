/* 
    Unit tests for Lab 5
    Authors: David Green, Sam Satalof, Sam Owens 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "ts_lcd.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "hardware/adc.h"
#include "user_interface.h"
#include <limits.h>

struct buttonPressed pressLoc;
char buf [2];

int main()
{   
    // Unit Test T:
    // drawInterface();
    // displayDiv0(); 
    // displayErr();

    // Unit Test T:
    // drawInterface();
    // buf[1] = '\0';
    // while (1) {
    //     pressLoc = getButton(pressLoc);
    //     if (pressLoc.depressed) {
    //         sprintf(buf, "%c", pressLoc.which_one);
    //         tft_setCursor(10, 10);
    //         tft_writeString(buf);
    //     }
    // }
}