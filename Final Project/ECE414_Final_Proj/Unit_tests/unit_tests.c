#include "FSR_read.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main() {
    adc_init();

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    printf("sanity check");

    struct fsrStruct fsr;
    while (1) {
        fsr = fsr_read();
        printf("%d", fsr.FSR1);
        sleep_ms(1000);
    }
}