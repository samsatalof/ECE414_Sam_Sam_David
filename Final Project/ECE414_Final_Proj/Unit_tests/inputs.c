#include "inputs.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

// SPI configurations
#define SCK_GPIO 10
#define SDO_GPIO 11
#define SDI_GPIO 12
#define CS1_GPIO 13
#define CS2_GPIO 9
#define SPI_PORT spi1

#define VIBRATO_PIN 28

void fsr_read(uint16_t* fsr)
{
    uint16_t spi_write;
    uint16_t spi_read;

    // Channel 0, ADC 1
    spi_write = 0x0030;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+6) = spi_read;

    // Channel 1, ADC 1
    spi_write = 0x0032;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+7) = spi_read;

    // Channel 2, ADC 1
    spi_write = 0x0034;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+8) = spi_read;

    // Channel 3, ADC 1
    spi_write = 0x0036;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+9) = spi_read;

    // Channel 4, ADC 1
    spi_write = 0x0038;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+10) = spi_read;

    // Channel 5, ADC 1
    spi_write = 0x3A;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+11) = spi_read;

    // Channel 6, ADC 1
    spi_write = 0x003C;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+12) = spi_read;

    // Channel 7, ADC 1
    spi_write = 0x003E;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+1) = spi_read;
    

    //Deactivate ADC1 so we can switch to ADC2.
    gpio_put(CS1_GPIO, 1);

    // Channel 0, ADC 2
    spi_write = 0x0030;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+2) = spi_read;

    // Channel 1, ADC 2
    spi_write = 0x0032;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+3) = spi_read;

    // Channel 2, ADC 2
    spi_write = 0x0034;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+4) = spi_read;

    // Channel 3, ADC 2
    spi_write = 0x0036;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr+5) = spi_read;

    // Channel 6, ADC 2
    spi_write = 0x003C;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(fsr) = spi_read;

    gpio_put(CS1_GPIO, 1);
    gpio_put(CS2_GPIO, 1);
}

void slider_pot_read(uint16_t* settings) {
    uint16_t spi_write;
    uint16_t spi_read;

    gpio_put(CS1_GPIO, 1);

    // Channel 4, ADC 2
    spi_write = 0x0038;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(settings) = spi_read;

    // Channel 5, ADC 2
    spi_write = 0x003A;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(settings+1) = spi_read;

    // Channel 7, ADC 2
    spi_write = 0x003E;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    *(settings+2) = spi_read;

    gpio_put(CS2_GPIO, 1);
}

bool vibrato_button_read() {

}

void adc_init()
{
    // Initialize SPI channel (channel, baud rate set to 1.35MHz)
    spi_init(SPI_PORT, 1350000);
    // Format (channel, data bits per transfer, polarity, phase, order)
    spi_set_format(SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_init(SDI_GPIO);
    gpio_init(SCK_GPIO);
    gpio_init(SCK_GPIO);

    // Map SPI signals to GPIO ports
    gpio_set_function(SDI_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SCK_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SDO_GPIO, GPIO_FUNC_SPI);
    // gpio_set_function(CS_GPIO, GPIO_FUNC_SPI);

    gpio_init(CS1_GPIO);
    gpio_set_dir(CS1_GPIO, GPIO_OUT);
    gpio_put(CS1_GPIO, 1);

    gpio_init(CS2_GPIO);
    gpio_set_dir(CS2_GPIO, GPIO_OUT);
    gpio_put(CS2_GPIO, 1);
}