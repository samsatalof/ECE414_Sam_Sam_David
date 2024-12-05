/*
    Drives the status leds
    Authors: Sam Owens, Sam Satalof, David Green
*/

#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

typedef enum LEDSTATUS {
    PIANO,
    GUITAR
};

enum LEDSTATUS setStatus(enum LEDSTATUS status);

void led_init();

#endif