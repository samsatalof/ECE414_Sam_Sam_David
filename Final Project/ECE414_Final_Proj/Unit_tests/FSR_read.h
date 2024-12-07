/*
    Reads from ADC chips 1 and 2, using SPI, to take FSR inputs
    Authors: Sam Owens, Sam Satalof, David Green
*/

#ifndef FSR_READ_H
#define FSR_READ_H

#include <stdint.h>

void fsr_read(uint16_t* fsr);

void adc_init();

#endif