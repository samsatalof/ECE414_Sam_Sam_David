#include "sw_in.h"
#include <stdint.h>

#define PADCTL_GPIO16  (volatile uint32_t *) (0x4001c000u + 0x00000044u)
#define PADCTL_GPIO17  (volatile uint32_t *) (0x4001c000u + 0x00000048u)

void sw_in_init() {
    volatile uint32_t *pad16 = (PADCTL_GPIO16);
    volatile uint32_t *pad17 = (PADCTL_GPIO17);

    *pad16 |= 0x00000044;
    *pad17 |= 0x00000044;
}

bool sw_in_read1() {
    bool in;
    in = gpio_get(17);
    return in;
}

bool sw_in_read2() {
    bool in;
    in = gpio_get(16);
    return in;
}
