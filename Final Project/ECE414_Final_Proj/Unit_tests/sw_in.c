#include "sw_in.h"
#include <stdint.h>

// Pad control registers
#define PADCTL_GPIO28 (volatile uint32_t *)(0x4001c000u + 0x00000074u)

// GPIO inputs 0-29 as a 32 bit reg, from lowest on LSB to highest on bit 29
#define GPIO_IN_REG *(volatile uint32_t *)(0xd0000000u + 0x00000004u)

void sw_in_init()
{
    volatile uint32_t *pad28 = (PADCTL_GPIO28);

    *pad28 |= 0x000000C8;
    *pad28 &= 0xFFFFFFFB;
}

bool sw_in_read1()
{
    return ((GPIO_IN_REG >> 28) & 0x00000001);
}