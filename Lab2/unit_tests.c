#include "pico/stdlib.h"
#include "sw_in.h"
#include <stdint.h>
#include "led_out.h"
#include <stdbool.h>

int main() {
    bool in1, in2;
    uint8_t out;
    sw_in_init();
    led_out_init();
    while(1) {
        // Unit Test T1:
        // out = 0xFF;
        // led_out_write(out);

        // Unit Test T2:
        // in1 = sw_in_read1();
        // in2 = sw_in_read2();
        // if (!in1 || !in2) out = 0xFF;
    }
}
