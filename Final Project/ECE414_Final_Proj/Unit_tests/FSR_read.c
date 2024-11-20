#include "FSR_read.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <stdio.h>

// SPI configurations
#define SCK_GPIO 10
#define SDO_GPIO 11
#define SDI_GPIO 12
#define CS_GPIO 13
#define SPI_PORT spi1

uint16_t fsr_read()
{
    struct fsrStruct read;
    uint16_t spi_write;
    uint16_t spi_read;
    spi_write = 0x1800;

    gpio_put(CS_GPIO, 1);
    gpio_put(CS_GPIO, 0);

    spi_write16_read16_blocking(SPI_PORT, &spi_write, &spi_read, 1);
    // printf("%d", spi_write16_blocking(SPI_PORT, &spi_write, 1));
    // printf("%d", spi_read16_blocking(SPI_PORT, 0, &spi_read, 1));
    read.FSR1 = spi_read;

    gpio_put(CS_GPIO, 1);
    printf("%d\n",spi_read);
    return spi_read;
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

    gpio_init(CS_GPIO);
    gpio_set_dir(CS_GPIO, GPIO_OUT);
    gpio_put(CS_GPIO, 1);
}