#include "lcd_rpm.h"
#include <stdio.h>

enum LCD_States tick_fct(enum LCD_States LCD_State)
{
    switch (LCD_State)
    {
    case LCD_INIT:
        ts_lcd_init();
        // char outputBuffer[32];
        // sprintf(outputBuffer, "%s", "         ");
        // tft_writeString(outputBuffer);
        LCD_State = LCD_DISPLAYRPM;
        break;

    case LCD_DISPLAYRPM:
        LCD_State = LCD_DISPLAYRPM;
        displayRpm();
        break;
    }

    return LCD_State;
}

void displayRpm()
{
    char outputBuffer[20];
    sprintf(outputBuffer, "Current RPM: %d", rpm);
    tft_setCursor(10, 10);
    tft_writeString(outputBuffer);
}