#include "lcd_rpm.h"

void displayRpm() {
    char outputBuffer[6];
    sprintf(outputBuffer, "%d", rpm);
    tft_setCursor(120,170);
    tft_writeString(outputBuffer);
}