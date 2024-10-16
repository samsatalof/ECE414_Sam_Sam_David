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

int main()
{
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

    }

    void
    tick()
    {

        switch (CALC_State)
        {
        case Operand:
            if (operand_overwrite = true)
            {
                CALC_State = Operand;
            }
            if (clr_pressed() = true)
            {
                CALC_State = CLR;
            }
            if (new_operator() = true)
            {
                CALC_State = Operator
            }

            break;
        case Operator:
            if (clr_pressed() = true)
            {
                CALC_State = CLR;
            }
            if (operator_overwrite() = true)
            {
                CALC_State = Operator;
            }
            if (new_operand() = true)
            {
                CALC_State = Operand_2;
            }

            break;
        case Operand_2:
            if (clr_pressed() = true)
            {
                CALC_State = CLR;
            }
            if (operand2_overwrite() = true)
            {
                CALC_State = Operand_2;
            }
            if (div_0_check() = true)
            {
                CALC_State = DIV_0;
            }
            if (overflow_check() = true)
            {
                CALC_State = Error;
            }
            if (eqls_pressed() = true)
            {
                CALC_State = Result;
            }

            break;
        case Result:
            if (clr_pressed() = true)
            {
                CALC_State = CLR;
            }
            break;
            if (clr_pressed() = false)
            {
                CALC_State = Result;
            }

        case DIV_0:
            if (clr_pressed() = true)
            {
                CALC_State = CLR;
            }
            if (clr_pressed() = false)
            {
                CALC_State = DIV_0;
            }
            break;
        case CLR:
            if (clr_pressed() = true)
            {
                CALC_State = CLR;
            }
            if (clr_pressed() = false)
            {
                CALC_State = Error;
            }
            if (boot_to_start() = true)
            {
                CALC_State = Operand;
            }

            break;
       
        }
         default;
            break;
    }
}