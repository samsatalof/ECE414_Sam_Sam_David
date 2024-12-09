/*
    Reads from ADC chips 1 and 2, using SPI, to take FSR inputs
    Authors: Sam Owens, Sam Satalof, David Green
*/

#ifndef SYNTH_CHIP_H
#define SYNTH_CHIP_H

#include <stdint.h>
#include <stdbool.h>

// typedef enum intrument_t {
//     PIANO,
//     TRUMPET,
//     CUSTOM
// };

typedef enum Note {
    C,
    Cs,
    D,
    Ds,
    E,
    F,
    Fs,
    G,
    Gs,
    A,
    As,
    B,
    Ch
};

//void set_rate_contdim_vibrato(bool rate, bool contdim, bool vibrato);

// Sets a register in the synth chip, register address specified with reg, sent value specified with data
void set_reg(uint8_t reg, uint8_t data);

// Initializes the channels in the synth chip
void init_ch();

// Plays a note, with note as either a value 0-11, or as Note enum C,Cs,D..., with channel a value 0-8, and octave 0-7 (4 is middle of the piano)
void play_note(enum Note note, uint8_t channel, uint8_t octave, uint16_t volume);

// Stops a channel playing a note
void clear_note(uint8_t channel);


void set_attack_decay(uint16_t atk, uint16_t decay);

void set_sustain(uint16_t intensity);

void set_vibrato(bool vibrato);

// Initializes everything necessary for the synth chip, and resets all registers to 0
void synth_init();

#endif