/*
    Module to draw user interface for the calculator.

    Authors: Sam Owens, Sam Satalof, David Green
*/
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

// Draws the interface for the calculator
void drawInterface();

// Displays the current value on the screen.
void displayResult(int result);

// Displays the current operator on the screen.
void displayOperator(char operator);

void displayDiv0();
void displayErr();

struct buttonPressed // Defines a struct for managing when buttons are pressed.
{
    bool depressed;
    char which_one;
};

// Make the struct extern so that it can be written to by user_interface.c and read from by calc.c.
extern struct buttonPressed buttonPressedStruct;

#endif