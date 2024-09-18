/* This module defines a function to initialize pins 16 and 17 to read from buttons, and configures them to use pull-up resistors.
 * It also defines two other functions, which read from sw1 and sw2 respectively, returning a bool value representing the input from the switch
 */

#ifndef SW_IN_H
#define SW_IN_H

#include "pico/stdlib.h"
#include <stdint.h>
#include <stdbool.h>

#define SW1_PIN 17
#define SW2_PIN 16

void sw_in_init();

bool sw_in_read1();

bool sw_in_read2();

#endif
