/* This module defines an init function which initializes ports 2-9 as outputs to drive leds,
 * as well as a function to map an 8-bit int val to the output ports, with the LSB mapped to gpio 2 and so on.
 */

#ifndef LED_OUT_H
#define LED_OUT_H

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdint.h>

void led_out_init();

void led_out_write(uint8_t val);

#endif
