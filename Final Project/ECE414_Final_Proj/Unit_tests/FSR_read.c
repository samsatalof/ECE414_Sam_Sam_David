#include "FSR_read.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

//SPI configurations
#define SCK_GPIO  10
#define SDO_GPIO  11
#define SDI_GPIO  12
#define CS_GPIO   13
#define SPI_PORT spi0

struct fsrStruct fsr_read() {
    struct fsrStruct read;
    uint16_t spi_write;
    uint16_t spi_read;

    spi_write = 0x0060;
    spi_write16_blocking(SPI_PORT, &spi_write, 1);
    spi_read16_blocking(SPI_PORT, 0, &spi_read, 1);
    read.FSR1 = spi_read;

    return read;
}

void adc_init() {
    stdio_init_all();

    // Initialize SPI channel (channel, baud rate set to 10MHz)
    spi_init(SPI_PORT, 10000000) ;
    // Format (channel, data bits per transfer, polarity, phase, order)
    spi_set_format(SPI_PORT, 16, 0, 0, 1);

    // Map SPI signals to GPIO ports
    gpio_set_function(SDI_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SCK_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SDO_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(CS_GPIO, GPIO_FUNC_SPI);
}