#include "pico/stdlib.h"
#include "sw_in.h"
#include "led_out.h"

main() {
    bool in1, in2;
    uint16_t out;
    sw_in_init();
    led_out_init();
    while(1) {
        in1 = sw_in_read1();
        in2 = sw_in_read2();

        if (in1 && in2) out = 0xFF;
        else if (in1 && !in2) out = 0x80;
        else if (!in1 && in2) out = 0x01;
        else out = 0x00;

        led_out_write(out);
    }
}