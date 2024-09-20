#include "sw_in.h"
#include <stdint.h>

void sw_in_init() {
    gpio_init(16);
    gpio_set_dir(16, GPIO_IN);
    gpio_pull_up(16);

    gpio_init(17);
    gpio_set_dir(17, GPIO_IN);
    gpio_pull_up(17);
}

bool sw_in_read1() {
    bool sw1val = gpio_get(17);
    return sw1val;
}

bool sw_in_read2() {
    bool sw2val = gpio_get(16);
    return sw2val;
}
