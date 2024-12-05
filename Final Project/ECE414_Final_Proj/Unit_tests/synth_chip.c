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
#define A0 21 // Address Write
#define WRN_GPIO 20 // Write
#define CSN_GPIO 19 // Chip select
#define ICN_GPIO 22 // Init clear 

void play_key1() {
    uint8_t spi_write;
    gpio_put(CSN_GPIO, 1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0xA0;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x98; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0xB0;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10); // Min: 3.35 for Address
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10);

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x31; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10);
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x20;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x01; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x40;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x10; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x60;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0xF0; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x80;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x77; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x23;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x01; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x43;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x00; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x63;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0xF0; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x83;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x77; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);
}

void play_key2() {
    uint8_t spi_write;
    gpio_put(CSN_GPIO, 1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0xA0;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x02; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0xB0;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10); // Min: 3.35 for Address
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10);

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x22; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10);
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x20;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x01; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x40;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x10; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x60;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0xF0; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x80;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x77; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x23;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x01; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x43;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x00; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x63;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0xF0; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);

    //Specify which register we are writing to in the synth chip.
    spi_write = 0x83;
    gpio_put(CSN_GPIO,0);
    gpio_put(A0, 0);
    // Write to shift register
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    // Write to synth chip
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1); 
    busy_wait_us(10); // Min: 3.35 for Address

    gpio_put(A0, 1);
    //Write data to the specified register within the Synth chip.
    spi_write = 0x77; //This is the note D.
    spi_write_blocking(SPI_SHIFT, &spi_write, 1);
    gpio_put(RCLK_GPIO, 0);
    busy_wait_us(1);
    gpio_put(RCLK_GPIO, 1);
    gpio_put(WRN_GPIO, 0);
    busy_wait_us(10);
    gpio_put(WRN_GPIO, 1);
    busy_wait_us(10); //Min : 23.74 fo Write
    gpio_put(CSN_GPIO, 1);
}

void synth_init() {
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
}