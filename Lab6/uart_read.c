#include "uart_read.h"

enum UART_States
{
    UART_Init,
    UART_Wait,
    UART_Input
};
enum UART_States UART_State;