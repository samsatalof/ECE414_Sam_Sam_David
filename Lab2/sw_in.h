#ifndef SW_IN_H
#define SW_IN_H

#include "pico/stdlib.h"
#include <stdbool.h>

#define SW1_PIN 17
#define SW2_PIN 16

void sw_in_init();

bool sw_in_read1();

bool sw_in_read2();

#endif