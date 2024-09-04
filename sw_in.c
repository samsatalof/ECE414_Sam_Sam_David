#include "sw_in.h"

#define GPIO16_SW2 *(volatile uint32_t *) (0x40014080)
#define GPIO17_SW1 *(volatile uint32_t *) (0x40014088)
#define PADCTL_GPIO16 *(volatile uint32_t *) (0x4001c044)
#define PADCTL_GPIO17 *(volatile uint32_t *) (0x4001c048)

void sw_in_init() {
    // GPIO 16/17 stat+ctrl is 0x40014000 offset 0x80/0x88
    *PADCTL_GPIO16 = 0x00000044;
    *PADCTL_GPIO17 = 0x00000044;
}

bool sw_in_read1() {
    digitalRead(17);
}

bool sw_in_read2() {
    digitalRead(16);
}