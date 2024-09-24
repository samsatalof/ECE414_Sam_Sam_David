#include "pico/stdlib.h"
#include "sw_in.h"
#include <stdint.h>
#include <stdlib.h>
#include "led_out.h"
#include <stdbool.h>
#include "timer.h"
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main()
{
    // Test T1:
    // led_out_init();
    // led_out_write(0xFF);

    // Test T2:
    // led_out_init();
    // sw_in_init();
    // while (1)
    // {
    //     if (!sw_in_read1())
    //     {
    //         led_out_write(0x80);
    //     }
    //     else if (!sw_in_read2())
    //     {
    //         led_out_write(0x01);
    //     }
    // }

    // Test T3:
    // stdio_init_all();
    // uart_init(UART_ID, BAUD_RATE);
    // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    // sw_in_init();
    // debounce_sw1_init();
    // debounce_sw2_init();
    // uint32_t t1, t2;
    // t1 = timer_read();
    // while (1)
    // {
    //     t2 = timer_read();
    //     if (timer_elapsed_ms(t1, t2) >= DEBOUNCE_PD_MS) {
    //         debounce_sw1_tick();
    //         debounce_sw2_tick();
    //         t1 = t2;
    //     }
    //     if (debounce_sw1_pressed())
    //     {
    //         printf("You have just pressed Button 1\n");
    //     }
    //     else if (debounce_sw2_pressed())
    //     {
    //         printf("You have just pressed Button 2\n");
    //     }
    // }

    // Test T4 is implemented in Lab3, labelled as such at the beginning of each FSM state.

    // Test T5 is also in Lab3
}