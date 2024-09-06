#include "sw_in.h"
#include <stdint.h>

#define PADCTL_GPIO16  (0x4001c000u + 0x00000044u)
#define PADCTL_GPIO17 (0x4001c000u + 0x00000048u)

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