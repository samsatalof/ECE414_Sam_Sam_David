#include "FSR_read.h"
#include "pico/stdlib.h"
#include "synth_chip.h"
#include <stdio.h>
#include "hardware/timer.h"
#include "timer.h"
#include <stdbool.h>

#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

uint16_t fsr[12]; // Stores the current read from fsr 0-11
bool playing[9]; // Stores whether channels 0-8 are currently playing, true means they are
uint8_t channel[12]; // Stores the channel that fsr 0-11 is playing on, if none then the value is 25

int main() {
    stdio_init_all();
    synth_init();
    init_ch();
    adc_init();

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    while (1)
    {
        fsr_read(fsr);
        for (uint8_t i = 0; i < 12; i++) {
            if (fsr[i] > 9000) {
                if (channel[i] != 25) {
                    play_note((enum Note) i, channel[i], 4);
                    printf("replaying note %d on channel %d", i, channel[i]);
                } else {
                    for (uint8_t j = 0; j < 9; j++) {
                        if(playing[j] == false) {
                            playing [j] = true;
                            channel[i] = j;
                            play_note((enum Note) i, j, 4);
                            printf("Newly playing note %d on channel %d, updated playing %d to %d", i, channel[i], j, playing[j]);
                            break;
                        }
                    }
                }
            } else {
                if (channel[i] != 25) {
                    printf("clearing fsr %d on channel %d", i, channel[i]);
                    clear_note(channel[i]);
                    playing[channel[i]] = false;
                    channel[i] = 25;
                }
            }
        }
    }
}