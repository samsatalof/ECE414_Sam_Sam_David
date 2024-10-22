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
#include <limits.h>

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

uint32_t operand1;
uint32_t operand2;
char operator;
uint32_t calculated_result;
bool operator2_specified;

int main()
{
}

bool overflowAdd(int original, int changeBy)
{
    if ((changeBy > 0) && (original > INT_MAX - changeBy))
    {
        CALC_State = Error;
        return true;
    }
    else
    {
        return false;
    }
}

bool overflowSub(int original, int changeBy)
{
    if ((changeBy < 0) && (original > INT_MAX + changeBy))
    {
        CALC_State = Error;
        return true;
    }
    else
    {
        return false;
    }
}

bool overflowMult(int original, int changeBy)
{
    if (original > INT_MAX / changeBy)
    {
        CALC_State = Error;
        return true;
    }
    else
    {
        return false;
    }
}

bool overflowDiv(int original, int changeBy)
{
    if ((changeBy == -1) && (original == INT_MIN))
    {
        CALC_State = Error;
        return true;
    }
    else
    {
        return false;
    }
}

void tick()
{
    switch (CALC_State)
    {
    case Operand:
        if (buttonPressedStruct.depressed == true)
        {
            // Append each new digit to the operand.
            // TODO --implement check for overflow if the user types too many digits into the calc.
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
            displayResult(operand1);
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
                displayOperator(operator);
                CALC_State = Operand_2;
            }
            else if (operator2_specified == false)
            {
                displayOperator(operator);
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
        if (buttonPressedStruct.depressed == true)
        {
            // Append each new digit to the operand.
            switch (buttonPressedStruct.which_one)
            {
            case '1':
                operand2 = (operand2 * 10) + 1;
                operator2_specified = true;
                break;
            case '2':
                operand2 = (operand2 * 10) + 2;
                operator2_specified = true;
                break;
            case '3':
                operand2 = (operand2 * 10) + 3;
                operator2_specified = true;
                break;
            case '4':
                operand2 = (operand2 * 10) + 4;
                operator2_specified = true;
                break;
            case '5':
                operand2 = (operand2 * 10) + 5;
                operator2_specified = true;
                break;
            case '6':
                operand2 = (operand2 * 10) + 6;
                operator2_specified = true;
                break;
            case '7':
                operand2 = (operand2 * 10) + 7;
                operator2_specified = true;
                break;
            case '8':
                operand2 = (operand2 * 10) + 8;
                operator2_specified = true;
                break;
            case '9':
                operand2 = (operand2 * 10) + 9;
                operator2_specified = true;
                break;
            default:
                // Do nothing if a non-numerical button has been pressed.
                break;
            }

            if (buttonPressedStruct.which_one = '=')
            {
                if (operand2 == 0)
                {
                    CALC_State = DIV_0;
                }
                else
                {
                    CALC_State = Result;
                }
            }
            else // Allow the user to continue their input of the second operand.
            {
                displayResult(operand2);
                CALC_State = Operand_2;
            }
        }
        break;
        // Performs the calculation.
    case Result: // TODO NEED TO IMPLEMENT OVERFLOW CHECKING!
                 // TODO NEED TO PRINT THE RESULT TO THE SCREEN!
        if (operator== '+')
        {
            calculated_result = operand1 + operand2;
            displayResult(calculated_result);
        }
        else if (operator== '-')
        {
            calculated_result = operand1 - operand2;
            displayResult(calculated_result);
        }
        else if (operator== '*')
        {
            calculated_result = operand1 * operand2;
            displayResult(calculated_result);
        }
        else if (operator== '/')
        {
            if (operand2 == 0)
            {
                CALC_State = DIV_0;
            }
            else
            {
                calculated_result == operand1 / operand2;
                displayResult(calculated_result);
            }
        }
        // Clears the result and allows the user to perform a new calculation.
        else if (buttonPressedStruct.depressed == true && buttonPressedStruct.which_one == 'C')
        {
            CALC_State = CLR;
        }
        // Allow the user to hit the equals button more than once in a row.
        else if (buttonPressedStruct.depressed == true && buttonPressedStruct.which_one == '=')
        {
            CALC_State = Result;
            // displayResult(calculated_result); --THIS MIGHT BE NEEDED, MIGHT BE REDUNDANT.
        }
        break;
    case DIV_0:
        displayDiv0();
        if (buttonPressedStruct.depressed == true && buttonPressedStruct.which_one == 'C')
        {
            CALC_State = CLR;
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
            displayResult(0);
            CALC_State = Operand;
        }
        break;
    case Error:
        displayErr();
        if (buttonPressedStruct.depressed == true && buttonPressedStruct.which_one == 'C')
        {
            CALC_State = CLR;
        }
        break;
    default:
        // Default case for state machine still needs to be implemented (if at all).
        break;
    }
}
