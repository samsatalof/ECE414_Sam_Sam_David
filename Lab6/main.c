#include "pid.h"
#include "uart_read.h"
#include "lcd_rpm.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include <stdint.h>

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UARTICR 0x40034044
#define UARTIMSC 0x40034038

// LCD variables
uint8_t LCD_time;
enum LCD_States LCD_State;

// PID variables
enum PID_States PID_State;
uint32_t rpm, temprpm;
uint16_t speed = 0x7000;

irq_handler_t controller() {
    LCD_time += 20;
    if (LCD_time >= 100) {
        LCD_State = LCD_tick(LCD_State);
        LCD_time = 0;
    }
    PID_State = PID_tick();
}

int main() {
    // UART Initialization
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // LCD Initialization
    ts_lcd_init();

    // PID Initialization
    gpio_set_function(15, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(15);
    pwm_set_clkdiv(slice_num, 1.9375);
    pwm_set_wrap(slice_num, 0xffff);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, speed);
    pwm_set_enabled(slice_num, true);
    ic_init();
    
    // Controller initialization

    irq_set_exclusive_handler(TIMER_IRQ_0);

    while(1);
}