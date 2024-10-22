#include "ts_lcd.h"
#include "TFTMaster.h"
#include <inttypes.h>
#include "TouchScreen.h"
#include <stdbool.h>
#include <stdio.h>
#include "user_interface.h"

uint16_t *px, *py; // Coordinates on the touchscreen
uint16_t x, y;
// Avoids malloc:
px = &x;
py = &y;
ts_lcd_init(); // init function

// Buffer for the display output of the calculator.
char outputBuffer[32];

void displayResult(int result)
{

    sprintf(outputBuffer, "%d", result);
    tft_setCursor(10, 10);
    tft_writeString(outputBuffer);
}

void displayOperator(char operator)
{
    sprintf(outputBuffer, "%s", operator);
    tft_setCursor(10, 10);
    tft_writeString(outputBuffer);
}

void displayErr(){
    sprintf(outputBuffer, "ERROR");
    tft_setCursor(10, 10);
    tft_writeString(outputBuffer);
}

void displayDiv0(){
    sprintf(outputBuffer, "DIV0");
    tft_setCursor(10, 10);
    tft_writeString(outputBuffer);
}

void drawInterface()
{
    char buf[2];
    buf[1] = '\0';
    ts_lcd_init();

    // Draw the Buttons:
    // Column 1:
    tft_drawRoundRect(4, 40, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(4, 90, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(4, 140, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(4, 190, 75, 45, 60, ILI9340_WHITE);
    // Column 2:
    tft_drawRoundRect(83, 40, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(83, 90, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(83, 140, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(83, 190, 75, 45, 60, ILI9340_RED);
    // Column 3:
    tft_drawRoundRect(162, 40, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(162, 90, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(162, 140, 75, 45, 60, ILI9340_WHITE);
    tft_drawRoundRect(162, 190, 75, 45, 60, ILI9340_BLUE);
    // Column 4:
    tft_drawRoundRect(241, 40, 75, 45, 60, ILI9340_YELLOW);
    tft_drawRoundRect(241, 90, 75, 45, 60, ILI9340_YELLOW);
    tft_drawRoundRect(241, 140, 75, 45, 60, ILI9340_YELLOW);
    tft_drawRoundRect(241, 190, 75, 45, 60, ILI9340_YELLOW);

    // Print the symbols onto the buttons:
    // Column 1:
    buf[0] = '7';
    tft_setCursor(34, 62);
    tft_writeString(buf);
    buf[0] = '4';
    tft_setCursor(34, 107);
    tft_writeString(buf);
    buf[0] = '1';
    tft_setCursor(34, 152);
    tft_writeString(buf);
    buf[0] = '0';
    tft_setCursor(34, 197);
    tft_writeString(buf);
    // Column 2:
    buf[0] = '8';
    tft_setCursor(109, 62);
    tft_writeString(buf);
    buf[0] = '5';
    tft_setCursor(109, 107);
    tft_writeString(buf);
    buf[0] = '2';
    tft_setCursor(109, 152);
    tft_writeString(buf);
    buf[0] = 'C';
    tft_setCursor(109, 197);
    tft_writeString(buf);
    // Column 3:
    buf[0] = '9';
    tft_setCursor(184, 62);
    tft_writeString(buf);
    buf[0] = '6';
    tft_setCursor(184, 107);
    tft_writeString(buf);
    buf[0] = '3';
    tft_setCursor(184, 152);
    tft_writeString(buf);
    buf[0] = '=';
    tft_setCursor(184, 197);
    tft_writeString(buf);
    // Column 4:
    buf[0] = '+';
    tft_setCursor(259, 62);
    tft_writeString(buf);
    buf[0] = '-';
    tft_setCursor(259, 107);
    tft_writeString(buf);
    buf[0] = 'X';
    tft_setCursor(259, 152);
    tft_writeString(buf);
    buf[0] = '/';
    tft_setCursor(259, 197);
    tft_writeString(buf);
}

// Figure out which button was pressed
struct buttonPressed getButton()
{
    if (get_ts_lcd(px, py))
    {
        if ((px != NULL) && (py != NULL)) // Checks the pointers aren't NULL
        {
            buttonPressedStruct.depressed = true;

            // First check which column, then check which row within each column.
            if ((px > 4) && (px < 79)) // Column 1
            {
                if ((py > 40) && (py < 85)) // Row 1
                {
                    buttonPressedStruct.which_one = '7';
                }
                else if ((py > 90) && (py < 135)) // Row 2
                {
                    buttonPressedStruct.which_one = '4';
                }
                else if ((py > 140) && (py < 185)) // Row 3
                {
                    buttonPressedStruct.which_one = '1';
                }
                else if ((py > 190) && (py < 235)) // Row 4
                {
                    buttonPressedStruct.which_one = '0';
                }
                else
                {
                    // User pressed outside any of the buttons.
                    buttonPressedStruct.which_one = 'F'; // Failure code --potential unused
                }
            }
            else if ((px > 83) && (px < 158)) // Column 2
            {
                if ((py > 40) && (py < 85)) // Row 1
                {
                    buttonPressedStruct.which_one = '8';
                }
                else if ((py > 90) && (py < 135)) // Row 2
                {
                    buttonPressedStruct.which_one = '5';
                }
                else if ((py > 140) && (py < 185)) // Row 3
                {
                    buttonPressedStruct.which_one = '2';
                }
                else if ((py > 190) && (py < 235)) // Row 4
                {
                    buttonPressedStruct.which_one = 'C';
                }
                else
                {
                    // User pressed outside any of the buttons.
                    buttonPressedStruct.which_one = 'F'; // Failure code --potential unused
                }
            }
            else if ((px > 162) && (px < 237)) // Column 3
            {
                if ((py > 40) && (py < 85)) // Row 1
                {
                    buttonPressedStruct.which_one = '9';
                }
                else if ((py > 90) && (py < 135)) // Row 2
                {
                    buttonPressedStruct.which_one = '6';
                }
                else if ((py > 140) && (py < 185)) // Row 3
                {
                    buttonPressedStruct.which_one = '3';
                }
                else if ((py > 190) && (py < 235)) // Row 4
                {
                    buttonPressedStruct.which_one = '=';
                }
                else
                {
                    // User pressed outside any of the buttons.
                    buttonPressedStruct.which_one = 'F'; // Failure code --potential unused
                }
            }
            else if ((px > 241) && (px < 316)) // Column 4
            {
                if ((py > 40) && (py < 85)) // Row 1
                {
                    buttonPressedStruct.which_one = '+';
                }
                else if ((py > 90) && (py < 135)) // Row 2
                {
                    buttonPressedStruct.which_one = '-';
                }
                else if ((py > 140) && (py < 185)) // Row 3
                {
                    buttonPressedStruct.which_one = '*';
                }
                else if ((py > 190) && (py < 235)) // Row 4
                {
                    buttonPressedStruct.which_one = '/';
                }
                else
                {
                    // User pressed outside any of the buttons.
                    buttonPressedStruct.which_one = 'F'; // Failure code --potential unused
                }
            }
            else
            {
                // User pressed outside any of the buttons.
                buttonPressedStruct.which_one = 'F'; // Failure code --potential unused
            }
        }
    }
    else
    {
        buttonPressedStruct.depressed = false;
    }
}