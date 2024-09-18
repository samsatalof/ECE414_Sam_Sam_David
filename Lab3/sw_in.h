/* This module initalizes the switches and reads from them. 
  By: Sam Owens, Sam Satalof and David Green */

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