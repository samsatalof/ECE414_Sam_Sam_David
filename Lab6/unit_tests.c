#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#include <stdio.h>
#include "timer.h"
#include "uart_read.h"

uint8_t *s;
uint8_t *p;
uint8_t *i;
uint8_t *d;

int main()
{
    // Unit Test 4
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uint32_t t1, t2;
    t1 = timer_read();

    // Assign parameters with default starting values.
    *s = 0;
    *p = 0;
    *i = 0;
    *d = 0;
    uint32_t *intermediate_number = 0;
    char *intermediate_cmd;
    char *user_in[32];

    while (1)
    {
        printf("Current parameters:");
        printf("target-rate         s: %d\r", s);
        printf("proportional-gain   p: %d\r", p);
        printf("integral-gain       i: %d\r", i);
        printf("derivative-gain     d: %d\r", d);
        printf("If you would like to change a value, type the cooresponding letter followed by a space and the new numerical value\r");
        scanf("&s", *user_in);
        getcmd(*user_in, *intermediate_cmd, *intermediate_number);
        if (*intermediate_cmd == 's')
        {
            *s = *intermediate_number;
        }
        else if (*intermediate_cmd == 'p')
        {
            *p = *intermediate_number;
        }
        else if (*intermediate_cmd = 'i')
        {
            *i = *intermediate_number;
        }
        else if (*intermediate_cmd = 'd')
        {
            *d = *intermediate_number;
        }

        t2 = timer_read();
        if (timer_elapsed_ms(t1, t2) >= 1000) // 1 second interval for timer
        {
            // Put code to run based on timer pulses here:
            t1 = t2;
        }
    }
}