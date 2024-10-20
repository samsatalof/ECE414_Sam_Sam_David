/* Main program for Lab05 Calculator
This program contains the state machine that performs the arithmetical functions of the calculator.
David Green, Sam Satalof, Sam Owens */

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

// FSM States:
enum CALC_States
{
    Operand,
    Operator,
    Operand_2,
    Result,
    DIV_0,
    Error,
    CLR
};
enum CALC_States CALC_State; // Create an instance of the enum.

u_int32_t operand1;
u_int32_t operand2;
char operator;
u_int32_t calculated_result;
bool operator2_specified;

int main()
{
}

void tick()
{
    switch (CALC_State)
    {
    case Operand:
        if (buttonPressedStruct.depressed == true)
        {
            // Append each new digit to the operand.
            switch (buttonPressedStruct.which_one)
            {
            case '1':
                operand1 = (operand1 * 10) + 1;
                break;
            case '2':
                operand1 = (operand1 * 10) + 2;
                break;
            case '3':
                operand1 = (operand1 * 10) + 3;
                break;
            case '4':
                operand1 = (operand1 * 10) + 4;
                break;
            case '5':
                operand1 = (operand1 * 10) + 5;
                break;
            case '6':
                operand1 = (operand1 * 10) + 6;
                break;
            case '7':
                operand1 = (operand1 * 10) + 7;
                break;
            case '8':
                operand1 = (operand1 * 10) + 8;
                break;
            case '9':
                operand1 = (operand1 * 10) + 9;
                break;
            default:
                // Do nothing if a non-numerical button has been pressed.
                break;
            }
            CALC_State = Operand;
        }
        // If the clear button is pressed, move to clear state.
        if (buttonPressedStruct.depressed == true && buttonPressedStruct.which_one == 'C')
        {
            CALC_State = CLR;
        }
        // If an operand already has been input and a new operator has been entered, move to the operator state.
        if (buttonPressedStruct.depressed == true && (buttonPressedStruct.which_one == '+' || buttonPressedStruct.which_one == '-' || buttonPressedStruct.which_one == '*' || buttonPressedStruct.which_one == '/'))
        {
            CALC_State = Operator;
        }
        break;
    case Operator:
        if (clr_pressed() == true)
        {
            CALC_State = CLR;
        }
        if (buttonPressedStruct.depressed == true)
        {
            if (buttonPressedStruct.which_one == '+')
            {
                operator= '+';
            }
            else if (buttonPressedStruct.which_one == '-')
            {
                operator= '-';
            }
            else if (buttonPressedStruct.which_one == '*')
            {
                operator= '*';
            }
            else if (buttonPressedStruct.which_one == '/')
            {
                operator= '/';
            }
            // Allow the operator to be continuously overwritten until another operand is input.
            if (operator2_specified == false && (buttonPressedStruct.which_one == '1' || buttonPressedStruct.which_one == '2' || buttonPressedStruct.which_one == '3' || buttonPressedStruct.which_one == '4' || buttonPressedStruct.which_one == '5' || buttonPressedStruct.which_one == '6' || buttonPressedStruct.which_one == '7' || buttonPressedStruct.which_one == '8' || buttonPressedStruct.which_one == '9'))
            {
                CALC_State = Operand_2;
            }
            else if (operator2_specified == false)
            {
                CALC_State = Operator;
            }
        }
        break;
    case Operand_2:
        // If the clear button is pressed, move to clear state.
        if (buttonPressedStruct.depressed == true && buttonPressedStruct.which_one == 'C')
        {
            CALC_State = CLR;
        }
        if (operand2_overwrite() == true)
        {
            CALC_State = Operand_2;
        }
        if (div_0_check() == true)
        {
            CALC_State = DIV_0;
        }
        if (overflow_check() == true)
        {
            CALC_State = Error;
        }
        if (eqls_pressed() == true)
        {
            CALC_State = Result;
        }

        break;
    case Result:
        if (clr_pressed() == true)
        {
            CALC_State = CLR;
        }
        break;
        if (clr_pressed() == false)
        {
            CALC_State = Result;
        }

    case DIV_0:
        if (clr_pressed() == true)
        {
            CALC_State = CLR;
        }
        if (clr_pressed() == false)
        {
            CALC_State = DIV_0;
        }
        break;
    case CLR:
        // If the clear button is pressed, reset the calculator registers and return to the initial state.
        if (clr_pressed() == true)
        {
            operand1 = 0;
            operator= 'F';
            operand2 = 0;
            calculated_result = 0;
            buttonPressedStruct.depressed = false;
            buttonPressedStruct.which_one = 'F';
            operator2_specified = false;
            CALC_State = Operand;
        }
        if (clr_pressed() == false)
        {
            CALC_State = Error; // WRONG CODE HERE! THIS DOESN"T MAKE SENSE!
        }
        if (boot_to_start() == true)
        {
            CALC_State = Operand;
        }
        break;
    default:
        // Default case for state machine still needs to be implemented.
        break;
    }
}
