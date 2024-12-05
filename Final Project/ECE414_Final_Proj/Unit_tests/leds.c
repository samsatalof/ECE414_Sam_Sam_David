#include "leds.h"
#include "pico/stdlib.h"

#define R_GPIO 26
#define G_GPIO 27
#define B_GPIO 28

enum LEDSTATUS setStatus(enum LEDSTATUS status) {

}

void led_init() {
    gpio_init(R_GPIO);
    gpio_set_dir(R_GPIO, GPIO_OUT);
    gpio_init(G_GPIO);
    gpio_set_dir(G_GPIO, GPIO_OUT);
    gpio_init(B_GPIO);
    gpio_set_dir(B_GPIO, GPIO_OUT);
}