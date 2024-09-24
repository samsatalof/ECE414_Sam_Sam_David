#include "sw_in.h"
#include <stdint.h>

// Pad control registers
#define PADCTL_GPIO16 (volatile uint32_t *)(0x4001c000u + 0x00000044u)
#define PADCTL_GPIO17 (volatile uint32_t *)(0x4001c000u + 0x00000048u)

// GPIO inputs 0-29 as a 32 bit reg, from lowest on LSB to highest on bit 29
#define GPIO_IN_REG *(volatile uint32_t *)(0xd0000000u + 0x00000004u)

void sw_in_init()
{
    volatile uint32_t *pad16 = (PADCTL_GPIO16);
    volatile uint32_t *pad17 = (PADCTL_GPIO17);

    *pad16 |= 0x000000C8;
    *pad17 |= 0x000000C8;
    *pad16 &= 0xFFFFFFFB;
    *pad17 &= 0xFFFFFFFB;
}

bool sw_in_read1()
{
    return ((GPIO_IN_REG >> 17) & 0x00000001);
}

bool sw_in_read2()
{
    return ((GPIO_IN_REG >> 16) & 0x00000001);
}