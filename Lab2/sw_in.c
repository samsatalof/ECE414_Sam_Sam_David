#include "sw_in.h"
#include <stdint.h>

#define GPIO16_SW2 *(volatile uint32_t *) (IO_BANK0_BASE + IO_BANK0_GPIO17_STATUS_OFFSET)
#define GPIO17_SW1 *(volatile uint32_t *) (IO_BANK0_BASE + IO_BANK0_GPIO16_STATUS_OFFSET)
#define PADCTL_GPIO16  (PADS_BANK0_BASE + PADS_BANK0_GPIO16_OFFSET)
#define PADCTL_GPIO17 (PADS_BANK0_BASE + PADS_BANK0_GPIO17_OFFSET)

void sw_in_init() {
    volatile uint32_t *pad16 = (PADCTL_GPIO16);
    volatile uint32_t *pad17 = (PADCTL_GPIO17);
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