/*
    Defines functions necessary to display RPM on the LCD screen
    Authors: Samuel Owens, David Green, Sam Satalof
*/

#ifndef LCD_RPM_H
#define LCD_RPM_H

#include "ic.h"
#include "TFTMaster.h"
#include "ts_lcd.h"
#include "pico/stdlib.h"

enum lcdStates
{
    LCD_INIT,
    LCD_DISPLAYRPM
};

void displayRpm();

#endif