/*
    Reads from ADC chips 1 and 2, using SPI, to take FSR inputs
    Authors: Sam Owens, Sam Satalof, David Green
*/

#ifndef SYNTH_CHIP_H
#define SYNTH_CHIP_H

#include <stdint.h>

// typedef enum intrument_t {
//     PIANO,
//     TRUMPET,
//     CUSTOM
// };

//void set_rate_contdim_vibrato(bool rate, bool contdim, bool vibrato);

//void set_reg(uint8_t reg, uint8_t data);

void play_key1();

void play_key2();

//void play_key3();

//void init_ch1();

// void set_volume(uint8_t vol);

// void set_attack_decay(uint8_t atk, uint8_t decay);

// void set_sustain_release(uint8_t sust, uint8_t release);

// void set_instrument(enum intrument_t inst);

void synth_init();

#endif