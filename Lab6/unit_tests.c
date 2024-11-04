#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "uart_read.h"
#include "pico/stdlib.h"
#include "ic.h"
#include "ts_lcd.h"
#include "TFTMaster.h"
#include "hardware/pwm.h"

uint8_t *s;
uint8_t *p;
uint8_t *i;
uint8_t *d;

int main()
{
    /*
    // Unit Test 1 --Test the ability to read and write data from the phototransistor
    // Monitor GPIO Pin 14 to see when it is held high or low. Print a message to the LCD depending on this state.
    stdio_init_all();
    gpio_init(14);
    gpio_set_dir(14, GPIO_IN);
    ts_lcd_init();
    tft_setCursor(10, 10);
    char outputBuffer[40];

    while (1)
    {
        bool photoTransistorValue = gpio_get(14);
        if (photoTransistorValue == false)
        {
            printf("Phototransistor Blocked");
            sprintf(outputBuffer, "Phototransistor Blocked");
        }
        else if (photoTransistorValue == true)
        {
            sprintf(outputBuffer, "Phototransistor Unblocked");
            printf("Phototransistor Unblocked");
        }
        busy_wait_ms(100);
        tft_writeString(outputBuffer);
    } */

    // Unit Test 1.5 --continued
    /*
    printf("Demo of interrupt-drive Input Capture\n");
    ic_init();
    while (1)
    {
        uint32_t rpm = ic_getrpm();
        printf("rpm=%d\n", rpm);
        sleep_ms(1000);
    }*/

    /*
    // Unit Test 2 --Test the ability to read and write data with the UART
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

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
        scanf("%s", *user_in);
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
    }*/

    // Unit Test 3 --Demonstrate imprecise control of the motor with PWM Signal
    stdio_init_all();
    gpio_set_function(15, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(15);
    pwm_set_clkdiv(slice_num, 1.9375);
    pwm_set_wrap(slice_num, 0xffff);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0x8000);
    pwm_set_enabled(slice_num, true);
    while(1);
}