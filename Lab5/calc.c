/* Main program for Lab05 Calculator
This program contains the state machine that performs the arithmetical functions of the calculator.
David Green, Sam Satalof, Sam Owens */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "ts_lcd.h"
#include "timer.h"
#include "TFTMaster.h"
#include "TouchScreen.h"
#include "hardware/adc.h"
#include "user_interface.h"
#include "hardware/timer.h"
#include "hardware/structs/timer.h"
#include "hardware/irq.h"
#include <limits.h>

#define ALARM_NUM 0
#define ALARM_IRQ TIMER_IRQ_0

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

int32_t operand1;
int32_t operand2;
char operator;
char operatorNext;
int32_t calculated_result;
bool operator2_specified, goToOperator;
struct buttonPressed pressLoc;
// static volatile bool alarm_fired;

bool overflowAdd(int original, int changeBy)
{
    if ((original + changeBy < INT_MIN) || (original + changeBy > INT_MAX))
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
    if ((original - changeBy < INT_MIN) || (original - changeBy > INT_MAX))
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
        if (pressLoc.depressed == true)
        {
            // Append each new digit to the operand.
            switch (pressLoc.which_one)
            {
            case '0':
                if (!overflowAdd(operand1, ((operand1 * 10)) - operand1))
                {
                    operand1 = (operand1 * 10);
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '1':
                if (!overflowAdd(operand1, ((operand1 * 10) + 1) - operand1))
                {
                    operand1 = (operand1 * 10) + 1;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '2':
                if (!overflowAdd(operand1, ((operand1 * 10) + 2) - operand1))
                {
                    operand1 = (operand1 * 10) + 2;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '3':
                if (!overflowAdd(operand1, ((operand1 * 10) + 3) - operand1))
                {
                    operand1 = (operand1 * 10) + 3;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '4':
                if (!overflowAdd(operand1, ((operand1 * 10) + 4) - operand1))
                {
                    operand1 = (operand1 * 10) + 4;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '5':
                if (!overflowAdd(operand1, ((operand1 * 10) + 5) - operand1))
                {
                    operand1 = (operand1 * 10) + 5;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '6':
                if (!overflowAdd(operand1, ((operand1 * 10) + 6) - operand1))
                {
                    operand1 = (operand1 * 10) + 6;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '7':
                if (!overflowAdd(operand1, ((operand1 * 10) + 7) - operand1))
                {
                    operand1 = (operand1 * 10) + 7;
                    displayResult(operand1);
                    CALC_State = Operand;
                    break;
                }
            case '8':
                if (!overflowAdd(operand1, ((operand1 * 10) + 8) - operand1))
                {
                    operand1 = (operand1 * 10) + 8;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case '9':
                if (!overflowAdd(operand1, ((operand1 * 10) + 9) - operand1))
                {
                    operand1 = (operand1 * 10) + 9;
                    displayResult(operand1);
                    CALC_State = Operand;
                }
                break;
            case 'C':
                // If the clear button is pressed, move to clear state.
                CALC_State = CLR;
                break;
            case 'N':
                operand1 = -operand1;
                displayResult(operand1);
                CALC_State = Operand;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                // If an operand already has been input and a new operator has been entered, move to the operator state.
                CALC_State = Operator;
                operator= pressLoc.which_one;
                displayOperator(operator);
                break;
            default:
                // Do nothing if no valid button was pressed
                break;
            }
        }
        break;
    case Operator:
        if (pressLoc.depressed == true)
        {
            if ((pressLoc.which_one == '+') || (pressLoc.which_one == '-') || (pressLoc.which_one == '*') || (pressLoc.which_one == '/'))
            {
                CALC_State = Operator;
                operator= pressLoc.which_one;
                displayOperator(operator);
            }
            else if (pressLoc.which_one == 'C')
            {
                CALC_State = CLR;
            }
            // Allow the operator to be continuously overwritten until another operand is input.
            else if ((pressLoc.which_one == '0' || pressLoc.which_one == '1' || pressLoc.which_one == '2' || pressLoc.which_one == '3' || pressLoc.which_one == '4' || pressLoc.which_one == '5' || pressLoc.which_one == '6' || pressLoc.which_one == '7' || pressLoc.which_one == '8' || pressLoc.which_one == '9'))
            {
                switch (pressLoc.which_one)
                {
                case '0':
                    operand2 = 0;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '1':
                    operand2 = 1;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '2':
                    operand2 = 2;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '3':
                    operand2 = 3;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '4':
                    operand2 = 4;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '5':
                    operand2 = 5;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '6':
                    operand2 = 6;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '7':
                    operand2 = 7;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                case '8':
                    operand2 = 8;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                case '9':
                    operand2 = 9;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                default:
                    // Do nothing if a non-numerical button has been pressed.
                    break;
                }
            }
        }
        break;
    case Operand_2:
        if (pressLoc.depressed == true)
        {
            // Append each new digit to the operand.
            switch (pressLoc.which_one)
            {
            case '0':
                if (!overflowAdd(operand2, ((operand2 * 10)) - operand2))
                {
                    operand2 = (operand2 * 10);
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '1':
                if (!overflowAdd(operand2, ((operand2 * 10) + 1) - operand2))
                {
                    operand2 = (operand2 * 10) + 1;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '2':
                if (!overflowAdd(operand2, ((operand2 * 10) + 2) - operand2))
                {
                    operand2 = (operand2 * 10) + 2;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '3':
                if (!overflowAdd(operand2, ((operand2 * 10) + 3) - operand2))
                {
                    operand2 = (operand2 * 10) + 3;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '4':
                if (!overflowAdd(operand2, ((operand2 * 10) + 4) - operand2))
                {
                    operand2 = (operand2 * 10) + 4;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '5':
                if (!overflowAdd(operand2, ((operand2 * 10) + 5) - operand2))
                {
                    operand2 = (operand2 * 10) + 5;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '6':
                if (!overflowAdd(operand2, ((operand2 * 10) + 6) - operand2))
                {
                    operand2 = (operand2 * 10) + 6;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '7':
                if (!overflowAdd(operand2, ((operand2 * 10) + 7) - operand2))
                {
                    operand2 = (operand2 * 10) + 7;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                    break;
                }
            case '8':
                if (!overflowAdd(operand2, ((operand2 * 10) + 8) - operand2))
                {
                    operand2 = (operand2 * 10) + 8;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case '9':
                if (!overflowAdd(operand2, ((operand2 * 10) + 9) - operand2))
                {
                    operand2 = (operand2 * 10) + 9;
                    displayResult(operand2);
                    CALC_State = Operand_2;
                }
                break;
            case 'C':
                // If the clear button is pressed, move to clear state.
                CALC_State = CLR;
                break;
            case 'N':
                operand2 = -operand2;
                displayResult(operand2);
                CALC_State = Operand_2;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                CALC_State = Result;
                operatorNext = pressLoc.which_one;
                goToOperator = true;
                break;
            case '=':
                CALC_State = Result;
            default:
                // Do nothing if a non-numerical button has been pressed.
                break;
            }
        }
        break;
        // Performs the calculation.
    case Result:
        if (operator== '+')
        {
            if (!overflowAdd(operand1, operand2))
            {
                calculated_result = operand1 + operand2;
                displayResult(calculated_result);
                if (goToOperator)
                {
                    operator= operatorNext;
                    CALC_State = Operator;
                    goToOperator = false;
                    operand1 = calculated_result;
                    displayOperator(operator);
                }
                else
                {
                    operator= 'F';
                }
            }
            else
            {
                CALC_State = Error;
            }
        }
        else if (operator== '-')
        {
            if (!overflowSub(operand1, operand2))
            {
                calculated_result = operand1 - operand2;
                displayResult(calculated_result);
                if (goToOperator)
                {
                    CALC_State = Operator;
                    goToOperator = false;
                    operator= operatorNext;
                    operand1 = calculated_result;
                    displayOperator(operator);
                }
                else
                {
                    operator= 'F';
                }
            }
            else
            {
                CALC_State = Error;
            }
        }
        else if (operator== '*')
        {
            if (!overflowMult(operand1, operand2))
            {
                calculated_result = operand1 * operand2;
                displayResult(calculated_result);
                if (goToOperator)
                {
                    CALC_State = Operator;
                    goToOperator = false;
                    operator= operatorNext;
                    operand1 = calculated_result;
                    displayOperator(operator);
                }
                else
                {
                    operator= 'F';
                }
            }
            else
            {
                CALC_State = Error;
            }
        }
        else if (operator== '/')
        {
            if (operand2 == 0)
            {
                CALC_State = DIV_0;
            }
            else
            {
                if (!overflowDiv(operand1, operand2))
                {
                    calculated_result = operand1 / operand2;
                    displayResult(calculated_result);
                    if (goToOperator)
                    {
                        CALC_State = Operator;
                        goToOperator = false;
                        operator= operatorNext;
                        operand1 = calculated_result;
                        displayOperator(operator);
                    }
                    else
                    {
                        operator= 'F';
                    }
                }
                else
                {
                    CALC_State = Error;
                }
            }
        }
        if (pressLoc.depressed && (pressLoc.which_one == '+' || pressLoc.which_one == '-' || pressLoc.which_one == '*' || pressLoc.which_one == '/'))
        {
            CALC_State = Operator;
            operator= pressLoc.which_one;
            operand1 = calculated_result;
            displayOperator(operator);
        }
        else if (pressLoc.depressed && (pressLoc.which_one == 'N')) {
            operand1 = -calculated_result;
            CALC_State = Operand;
        }
        // Clears the result and allows the user to perform a new calculation.
        else if (pressLoc.depressed == true && pressLoc.which_one == 'C')
        {
            CALC_State = CLR;
        }
        // Allow the user to hit the equals button more than once in a row.
        else if (pressLoc.depressed == true && pressLoc.which_one == '=')
        {
            CALC_State = Result;
        }
        break;
    case DIV_0:
        displayDiv0();
        if (pressLoc.depressed == true && pressLoc.which_one == 'C')
        {
            CALC_State = CLR;
        }
        break;
    case CLR:
        // If the clear button is pressed, reset the calculator registers and return to the initial state.
        operand1 = 0;
        operator= 'F';
        operand2 = 0;
        calculated_result = 0;
        displayResult(0);
        CALC_State = Operand;
        goToOperator = false;
        break;
    case Error:
        displayErr();
        if (pressLoc.depressed == true && pressLoc.which_one == 'C')
        {
            CALC_State = CLR;
        }
        break;
    default:
        // Default case for state machine still needs to be implemented (if at all).
        break;
    }
}

uint32_t t1, t2, t3, t4;
uint32_t gameTimer = 300;
#define DEBOUNCE_PD_MS 200

int main()
{
    drawInterface();
    CALC_State = CLR;
    t1 = timer_read();
    t3 = timer_read();
    while (1)
    {
        // Button Debounce Code
        t2 = timer_read();
        if (timer_elapsed_ms(t1, t2) >= DEBOUNCE_PD_MS)
        {
            pressLoc = getButton(pressLoc);
            t1 = t2;
        }
        // Tick the game state machine.
        pressLoc = getButton(pressLoc);
        t4 = timer_read();
        if (timer_elapsed_ms(t3, t4) >= gameTimer)
        {
            tick();
            t3 = t4;
        }
    }
}