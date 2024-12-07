/*
    Reads from ADC chips 1 and 2, using SPI, to take FSR, slider, and potentiometer inputs. Also reads from a button for vibrato
    Authors: Sam Owens, Sam Satalof, David Green
*/

#ifndef SETTING_CONTROL_H
#define SETTING_CONTROL_H

#include <stdint.h>

// Reads from sliders and pots
void slider_pot_read(uint16_t* settings);

// Reads from the vibrato on/off button
bool vibrato_button_read();

// Reads from the fsrs
void fsr_read(uint16_t* fsr);

// Initializes the adcs
void adc_init();

#endif