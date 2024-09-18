#include "led_out.h"
#include <stdint.h>

void led_out_init() {
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    gpio_init(3);
    gpio_set_dir(3, GPIO_OUT);
    gpio_init(4);
    gpio_set_dir(4, GPIO_OUT);
    gpio_init(5);
    gpio_set_dir(5, GPIO_OUT);
    gpio_init(6);
    gpio_set_dir(6, GPIO_OUT);
    gpio_init(7);
    gpio_set_dir(7, GPIO_OUT);
    gpio_init(8);
    gpio_set_dir(8, GPIO_OUT);
    gpio_init(9);
    gpio_set_dir(9, GPIO_OUT);
}

void led_out_write(uint8_t val) {
    gpio_put(2, val & 0x01);
    gpio_put(3, (val & 0x02) >> 1);
    gpio_put(4, (val & 0x04) >> 2);
    gpio_put(5, (val & 0x08) >> 3);
    gpio_put(6, (val & 0x10) >> 4);
    gpio_put(7, (val & 0x20) >> 5);
    gpio_put(8, (val & 0x40) >> 6);
    gpio_put(9, (val & 0x80) >> 7);
}
