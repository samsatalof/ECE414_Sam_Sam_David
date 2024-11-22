#include "synth_chip.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

// Shift Reg
#define SER_GPIO 3
#define SRCLK_GPIO 2
#define RCLK_GPIO 7


// OPL
#define D_GPIO 3
#define A0 21 // What is?
#define WRN_GPIO 20 // Write
#define CSN_GPIO 19 // Chip select
#define ICN_GPIO 22 // Init clear

