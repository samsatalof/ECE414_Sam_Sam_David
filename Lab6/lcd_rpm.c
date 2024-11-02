#include "lcd_rpm.h"

enum lcdStates lcdState;

tick_fct()
{
    switch (lcdState)
    {
    case LCD_INIT:
        ts_lcd_init();
        // char outputBuffer[32];
        // sprintf(outputBuffer, "%s", "         ");
        // tft_writeString(outputBuffer);
        lcdState = LCD_DISPLAYRPM;
        break;

    case LCD_DISPLAYRPM:
        lcdState = LCD_DISPLAYRPM;
        displayRpm();
        break;
    }
}

void displayRpm()
{
    char outputBuffer[20];
    sprintf(outputBuffer, "Current RPM: %d", rpm);
    tft_setCursor(10, 10);
    tft_writeString(outputBuffer);
}