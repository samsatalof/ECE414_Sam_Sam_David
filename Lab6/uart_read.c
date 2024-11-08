#include "uart_read.h"

enum UART_States
{
    UART_Init,
    UART_Wait,
    UART_Input
};
enum UART_States UART_State;

void getcmd(char *line, char *cmd, uint32_t *np)
{
    uint32_t num = 0;
    *cmd = *line;
    line += 2;
    while (*line != '\0')
    {
        num = num * 10 + (*line - '0');
        line++;
    }
    *np = num;
}
