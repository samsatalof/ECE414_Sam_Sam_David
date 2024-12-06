#include "FSR_read.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "synth_chip.h"
#include <stdio.h>
#include "hardware/timer.h"
#include "timer.h"
#include <stdbool.h>

uint32_t t1, t2;
bool play1;
int main()
{
    stdio_init_all();
    synth_init();
    init_ch1();
    scale();
    // play1 = false;
    // t1 = timer_read();
    // while (1)
    // {
    //     t2 = timer_read();
    //     if (timer_elapsed_ms(t1, t2) >= 2000)
    //     {
    //         if (play1) {
    //             play_key1();
    //             play1 = false;
    //         } else {
    //             play_key2();
    //             play1 = true;
    //         }
    //         t1 = t2;
    //     }
    // }
}

/*
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

    struct fsrStruct fsr;
    while (1)
    {
        fsr = fsr_read();
        printf(" ADC 1: %d %d %d %d %d %d %d %d, ADC 2: %d %d %d %d \r", fsr.FSR1, fsr.FSR2, fsr.FSR3, fsr.FSR4, fsr.FSR5, fsr.FSR6, fsr.FSR7, fsr.FSR8, fsr.FSR9, fsr.FSR10, fsr.FSR11, fsr.FSR12);
        sleep_ms(100);
    }
}*/