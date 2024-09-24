/* This module initalizes the LEDs and illuminates them according to the function inputs. 
  By: Sam Owens, Sam Satalof and David Green */

#ifndef LED_OUT_H
#define LED_OUT_H

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdint.h>

void led_out_init();

void led_out_write(uint8_t val);

#endif