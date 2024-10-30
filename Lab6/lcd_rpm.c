#include "lcd_rpm.h"

enum lcdStates lcdState;

tick_fct()
{
    switch (lcdState)
    {
    case LCD_INIT:
        lcdState = LCD_DISPLAYRPM;
        break;

    case LCD_DISPLAYRPM:
        lcdState = LCD_DISPLAYRPM;
        break;
    }

    switch (lcdState)
    {
    case LCD_INIT:
        break;

    case LCD_DISPLAYRPM:
        break;
    }
}

void displayRpm()
{
    char outputBuffer[6];
    sprintf(outputBuffer, "%d", rpm);
    tft_setCursor(120, 170);
    tft_writeString(outputBuffer);
}