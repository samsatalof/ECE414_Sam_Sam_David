/*
    Reads from ADC chips 1 and 2, using SPI, to take FSR inputs
    Authors: Sam Owens, Sam Satalof, David Green
*/

#ifndef FSR_READ_H
#define FSR_READ_H

#include <stdint.h>

typedef struct fsrStruct {
    uint16_t FSR1;
    uint16_t FSR2;
    uint16_t FSR3;
    uint16_t FSR4;
    uint16_t FSR5;
    uint16_t FSR6;
    uint16_t FSR7;
    uint16_t FSR8;
    uint16_t FSR9;
    uint16_t FSR10;
    uint16_t FSR11;
    uint16_t FSR12;
};

uint16_t fsr_read();

void adc_init();

#endif