#include "sw_in.h"

#define GPIO16_SW2 *(volatile uint32_t *) (IO_BANK0_BASE + IO_BANK0_GPIO17_STATUS_OFFSET)
#define GPIO17_SW1 *(volatile uint32_t *) (IO_BANK0_BASE + IO_BANK0_GPIO16_STATUS_OFFSET)
#define PADCTL_GPIO16 *(volatile uint32_t *) (PADS_BANK0_BASE + PADS_BANK0_GPIO16_OFFSET)
#define PADCTL_GPIO17 *(volatile uint32_t *) (PADS_BANK0_BASE + PADS_BANK0_GPIO17_OFFSET)

void sw_in_init() {
    // GPIO 16/17 stat+ctrl is 0x40014000 offset 0x80/0x88
    PADCTL_GPIO16 = 0x00000044;
    PADCTL_GPIO17 = 0x00000044;
}

bool sw_in_read1() {
    bool out;
    out = digitalRead(17);
    return out;
}

bool sw_in_read2() {
    bool out;
    out = digitalRead(16);
    return out;
}