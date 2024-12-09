#include "synth_chip.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

// Shift Reg
#define SER_GPIO 3
#define SRCLK_GPIO 2
#define RCLK_GPIO 7
#define SPI_SHIFT spi0

// OPL
#define D_GPIO 3
#define A0 21       // Address Write
#define WRN_GPIO 20 // Write
#define CSN_GPIO 19 // Chip select
#define ICN_GPIO 22 // Init clear

void set_reg(uint8_t reg, uint8_t data)
{
    // Make sure relevant signals are reset
    gpio_put(CSN_GPIO, 1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 1);

    // Specify which register we are writing to in the synth chip.
    gpio_put(CSN_GPIO, 0);                  // Select synth chip
    gpio_put(A0, 0);                        // Writing Address, not data
    spi_write_blocking(SPI_SHIFT, &reg, 1); // Write to shift reg
    // Store value in shift reg output
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); // Min: 3.35 for Address

    // Write data to synth chip reg
    gpio_put(A0, 1);                         // Writing data, not address
    spi_write_blocking(SPI_SHIFT, &data, 1); // Write to shift reg
    // Store value in shift reg output
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10);      // Min : 23.74 for Write
    gpio_put(CSN_GPIO, 1); // Deselect Synth chip, and end write cycle
}

// Call with note as either a value 0-11, or as Note enum C,Cs,D..., with channel a value 0-8, and octave 0-7 (4 is middle of the piano)
void play_note(enum Note note, uint8_t channel, uint8_t octave)
{
    uint8_t Areg, Breg;
    switch (note)
    {
    case C:
        Areg = 0xAE;
        Breg = 0x02 + ((octave - 1) << 2) + 0x20;
        break;
    case Cs:
        Areg = 0x6B;
        Breg = 0x01 + (octave << 2) + 0x20;
        break;
    case D:
        Areg = 0x81;
        Breg = 0x01 + (octave << 2) + 0x20;
        break;
    case Ds:
        Areg = 0x98;
        Breg = 0x01 + (octave << 2) + 0x20;
        break;
    case E:
        Areg = 0xB0;
        Breg = 0x01 + (octave << 2) + 0x20;
        break;
    case F:
        Areg = 0xCA;
        Breg = 0x01 + (octave << 2) + 0x20;
        break;
    case Fs:
        Areg = 0xE5;
        Breg = 0x01 + (octave << 2) + 0x20;
        break;
    case G:
        Areg = 0x02;
        Breg = 0x02 + (octave << 2) + 0x20;
        break;
    case Gs:
        Areg = 0x20;
        Breg = 0x02 + (octave << 2) + 0x20;
        break;
    case A:
        Areg = 0x41;
        Breg = 0x02 + (octave << 2) + 0x20;
        break;
    case As:
        Areg = 0x63;
        Breg = 0x02 + (octave << 2) + 0x20;
        break;
    case B:
        Areg = 0x87;
        Breg = 0x02 + (octave << 2) + 0x20;
        break;
    case Ch:
        Areg = 0xAE;
        Breg = 0x02 + (octave << 2) + 0x20;
        break;
    }
    set_reg((uint8_t) 0xA0 + (channel), Areg);
    set_reg((uint8_t) 0xB0 + (channel), Breg);
}

void clear_note(uint8_t channel)
{
    set_reg((uint8_t) 0xB0 + (channel), 0x00);
}

void init_ch()
{
    for (uint8_t i = 0; i < 3; i++) {
        set_reg(0x20+i, 0x01);
        set_reg(0x40+i, 0x10);
        set_reg(0x60+i, 0x73);
        set_reg(0x80+i, 0x77);
        set_reg(0x23+i, 0x01);
        set_reg(0x43+i, 0x00);
        set_reg(0x63+i, 0x73);
        set_reg(0x83+i, 0x77);
    }
    for (uint8_t i = 8; i < 12; i++) {
        set_reg(0x20+i, 0x01);
        set_reg(0x40+i, 0x10);
        set_reg(0x60+i, 0x73);
        set_reg(0x80+i, 0x77);
        set_reg(0x23+i, 0x01);
        set_reg(0x43+i, 0x00);
        set_reg(0x63+i, 0x73);
        set_reg(0x83+i, 0x77);
    }
    for (uint8_t i = 16; i < 19; i++) {
        set_reg(0x20+i, 0x01);
        set_reg(0x40+i, 0x10);
        set_reg(0x60+i, 0x73);
        set_reg(0x80+i, 0x77);
        set_reg(0x23+i, 0x01);
        set_reg(0x43+i, 0x00);
        set_reg(0x63+i, 0x73);
        set_reg(0x83+i, 0x77);
    }
}

void set_attack_decay(uint16_t atk, uint16_t decay) {
    uint8_t sentVal = 0x00;
    if (atk > 3200) {
        sentVal += ((atk/2173) << 4);
    }
    if (decay > 3200) {
       sentVal += (decay/2173);
    }
    for (uint8_t i = 0; i < 3; i++) {
        set_reg(0x60+i, sentVal);
        set_reg(0x63+i, sentVal);
    }
    for (uint8_t i = 8; i < 12; i++) {
        set_reg(0x60+i, sentVal);
        set_reg(0x63+i, sentVal);
    }
    for (uint8_t i = 16; i < 19; i++) {
        set_reg(0x60+i, sentVal);
        set_reg(0x63+i, sentVal);
    }
}

void set_vibrato(uint16_t intensity) {
    if (intensity > 11000) {
        uint8_t sentVal = ((intensity/1440) << 4) + 0x07;
        for (uint8_t i = 0; i < 3; i++) {
            set_reg(0x80+i, sentVal);
            set_reg(0x83+i, sentVal);
        }
        for (uint8_t i = 8; i < 12; i++) {
            set_reg(0x80+i, sentVal);
            set_reg(0x83+i, sentVal);
        }
        for (uint8_t i = 16; i < 19; i++) {
            set_reg(0x80+i, sentVal);
            set_reg(0x83+i, sentVal);
        }
    }
}

void synth_init()
{
    gpio_set_function(SER_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SRCLK_GPIO, GPIO_FUNC_SPI);

    // Initialize SPI channel (channel, baud rate set to 1.35MHz)
    spi_init(SPI_SHIFT, 1350000);
    // Format (channel, data bits per transfer, polarity, phase, order)
    spi_set_format(SPI_SHIFT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_init(RCLK_GPIO);
    gpio_set_dir(RCLK_GPIO, GPIO_OUT);
    gpio_init(A0);
    gpio_init(WRN_GPIO);
    gpio_init(ICN_GPIO);
    gpio_init(CSN_GPIO);
    gpio_init(ICN_GPIO);
    gpio_set_dir(A0, GPIO_OUT);
    gpio_set_dir(WRN_GPIO, GPIO_OUT);
    gpio_set_dir(CSN_GPIO, GPIO_OUT);
    gpio_set_dir(ICN_GPIO, GPIO_OUT);
    gpio_set_dir(ICN_GPIO, GPIO_OUT);

    // Reset synth chip
    gpio_put(ICN_GPIO, 1);
    busy_wait_us(20);
    gpio_put(ICN_GPIO, 0);
    busy_wait_us(20);
    gpio_put(ICN_GPIO, 1);

    uint16_t i = 0;
    for (uint16_t i = 0; i <= 245; i++)
    {
        set_reg(i, 0x00);
    }
}