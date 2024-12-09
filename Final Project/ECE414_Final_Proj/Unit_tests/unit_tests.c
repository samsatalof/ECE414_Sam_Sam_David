#include "inputs.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "synth_chip.h"
#include <stdio.h>
#include "hardware/timer.h"
#include "timer.h"
#include <stdbool.h>

// uint32_t t1, t2;
// bool play1;
// int main()
// {
//     stdio_init_all();
//     synth_init();
//     init_ch();
//     scale();
//     // play1 = false;
//     // t1 = timer_read();
//     // while (1)
//     // {
//     //     t2 = timer_read();
//     //     if (timer_elapsed_ms(t1, t2) >= 2000)
//     //     {
//     //         if (play1) {
//     //             play_key1();
//     //             play1 = false;
//     //         } else {
//     //             play_key2();
//     //             play1 = true;
//     //         }
//     //         t1 = t2;
//     //     }
//     // }
// }

uint16_t fsr[16];
uint16_t settings[3];

#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1
int main()
{
    adc_init();
    stdio_init_all();

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    printf("sanity check");

    while (1)
    {
        fsr_read(fsr);
        slider_pot_read(settings);
        printf(" ADC 1: %d %d %d %d %d %d %d %d, ADC 2: %d %d %d %d %d %d %d %d \r", fsr[0], fsr[1], fsr[2], fsr[3], fsr[4], fsr[5], fsr[6], fsr[7], fsr[8], fsr[9], fsr[10], fsr[11], fsr[12], settings[0], settings[1], settings[2]);
        sleep_ms(100);
    }
}