/*
    Defines functions necessary to take input PID values from the UART
    Authors: Samuel Owens, David Green, Sam Satalof
*/

#ifndef UART_READ_H
#define UART_READ_H

#include <stdint.h>

void getcmd(char *line, char *cmd, uint32_t *np);

#endif