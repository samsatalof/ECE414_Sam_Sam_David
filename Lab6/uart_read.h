/*
    Defines functions necessary to take input PID values from the UART
    Authors: Samuel Owens, David Green, Sam Satalof
*/

#ifndef UART_READ_H
#define UART_READ_H

void getcmd(char *line, char *cmd, int *np);

#endif