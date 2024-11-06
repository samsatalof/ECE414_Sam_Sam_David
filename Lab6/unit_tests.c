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

int main()
{
    // Unit Test 1 --Test the ability to read and write data from the phototransistor
    // Monitor GPIO Pin 14 to see when it is held high or low. Print a message to the LCD depending on this state.
    // stdio_init_all();
    // gpio_init(14);
    // gpio_set_dir(14, GPIO_IN);
    // ts_lcd_init();
    // tft_setCursor(10, 10);
    // char outputBuffer[40];

    // while (1)
    // {
    //     bool photoTransistorValue = gpio_get(14);
    //     if (photoTransistorValue == false)
    //     {
    //         printf("Phototransistor Blocked  \r");
    //         sprintf(outputBuffer, "Phototransistor Blocked");
    //     }
    //     else if (photoTransistorValue == true)
    //     {
    //         sprintf(outputBuffer, "Phototransistor Unblocked");
    //         printf("Phototransistor Unblocked\r");
    //     }
    //     busy_wait_ms(100);
    //     tft_writeString(outputBuffer);
    // }

    // Unit Test 3 --continued
    // uint32_t rpm, temprpm;
    // uint16_t speed = 0x7000;
    // printf("Demo of interrupt-drive Input Capture\n");
    // stdio_init_all();
    // gpio_set_function(15, GPIO_FUNC_PWM);
    // uint slice_num = pwm_gpio_to_slice_num(15);
    // pwm_set_clkdiv(slice_num, 1.9375);
    // pwm_set_wrap(slice_num, 0xffff);
    // pwm_set_chan_level(slice_num, PWM_CHAN_B, speed);
    // pwm_set_enabled(slice_num, true);
    // ic_init();
    // uint32_t t1, t2, t3, t4;
    // t1 = timer_read();
    // t3 = timer_read();
    // while (1)
    // {
    //     temprpm = ic_getrpm();
    //     if (temprpm != -1) {
    //         rpm = temprpm;
    //     }
    //     t2 = timer_read();
    //     if (timer_elapsed_ms(t1, t2) > 1000) {
    //         printf("rpm=%d\n", rpm);
    //         t1= t2;
    //     }
    //     t4 = timer_read();
    //     if (timer_elapsed_ms(t3, t4) > 8000) {
    //         speed += 0x1000;
    //         pwm_set_chan_level(slice_num, PWM_CHAN_B, speed);
    //         t3= t4;
    //     }
    // }

    // Unit Test 2 --Test the ability to read and write data with the UART
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Assign parameters with default starting values.
    uint8_t s1;
    uint8_t p1;
    uint8_t i1;
    uint8_t d1;

    uint8_t *s = &s1;
    uint8_t *p = &p1;
    uint8_t *i = &i1;
    uint8_t *d = &d1;

    *s = 0;
    *p = 0;
    *i = 0;
    *d = 0;

    uint32_t intermediate_number;
    uint32_t *intermediate_number1 = &intermediate_number;

    char intermediate_cmd;
    char user_in[32];

    while (1)
    {
        printf("Current parameters:");
        printf("target-rate         s: %d\r", s);
        printf("proportional-gain   p: %d\r", p);
        printf("integral-gain       i: %d\r", i);
        printf("derivative-gain     d: %d\r", d);
        printf("If you would like to change a value, type the cooresponding letter followed by a space and the new numerical value\n");
        scanf("%s", *user_in);
        getcmd(user_in, &intermediate_cmd, intermediate_number1);
        if (intermediate_cmd == 's')
        {
            *s = intermediate_number;
        }
        else if (intermediate_cmd == 'p')
        {
            *p = intermediate_number;
        }
        else if (intermediate_cmd = 'i')
        {
            *i = intermediate_number;
        }
        else if (intermediate_cmd = 'd')
        {
            *d = intermediate_number;
        }
    }

    // Unit Test X:
    // stdio_init_all();
    // gpio_set_function(15, GPIO_FUNC_PWM);
    // uint slice_num = pwm_gpio_to_slice_num(15);
    // pwm_set_clkdiv(slice_num, 1.9375);
    // pwm_set_wrap(slice_num, 0xffff);
    // pwm_set_chan_level(slice_num, PWM_CHAN_B, 0x8000);
    // pwm_set_enabled(slice_num, true);
    // gpio_init(14);
    // gpio_set_dir(14, GPIO_IN);
    // ts_lcd_init();
    // tft_setCursor(10, 10);
    // char outputBuffer[40];

    // while (1)
    // {
    //     bool photoTransistorValue = gpio_get(14);
    //     if (photoTransistorValue == false)
    //     {
    //         printf("Phototransistor Blocked  \r");
    //         sprintf(outputBuffer, "Phototransistor Blocked");
    //     }
    //     else if (photoTransistorValue == true)
    //     {
    //         sprintf(outputBuffer, "Phototransistor Unblocked");
    //         printf("Phototransistor Unblocked\r");
    //     }
    //     busy_wait_ms(100);
    //     tft_writeString(outputBuffer);
    // }
}