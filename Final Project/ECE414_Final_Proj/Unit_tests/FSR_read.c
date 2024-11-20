#include "FSR_read.h"
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

struct fsrStruct fsr_read()
{
    struct fsrStruct read;
    uint16_t spi_write;
    uint16_t spi_read;

    // Channel 0, ADC 1
    spi_write = 0x0030;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR1 = spi_read;

    // Channel 1, ADC 1
    spi_write = 0x0032;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR2 = spi_read;

    // Channel 2, ADC 1
    spi_write = 0x0034;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR3 = spi_read;

    // Channel 3, ADC 1
    spi_write = 0x0036;
    gpio_put(CS1_GPIO, 1);
    gpio_put(CS1_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR4 = spi_read;

    //Deactivate ADC1 so we can switch to ADC2.
    gpio_put(CS1_GPIO, 1);

    // Channel 0, ADC 2
    spi_write = 0x0030;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR5 = spi_read;

    // Channel 1, ADC 2
    spi_write = 0x0032;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR6 = spi_read;

    // Channel 2, ADC 2
    spi_write = 0x0034;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR7 = spi_read;

    // Channel 3, ADC 2
    spi_write = 0x0036;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR8 = spi_read;

    // // Channel 4, ADC 2
    spi_write = 0x0038;
    gpio_put(CS2_GPIO, 1);
    gpio_put(CS2_GPIO, 0);
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR9 = spi_read;

    gpio_put(CS1_GPIO, 1);
    gpio_put(CS2_GPIO, 1);
    return read;
}

void adc_init()
{
    stdio_init_all();

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