#include "inputs.h"
#include "debounce_sw1.h"
#include "pico/stdlib.h"
#include "synth_chip.h"
#include <stdio.h>
#include "hardware/timer.h"
#include "timer.h"
#include <stdbool.h>
#include "sw_in.h"

#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

uint16_t fsr[13]; // Stores the current read from fsr 0-12
bool playing[9]; // Stores whether channels 0-8 are currently playing, true means they are
uint8_t channel[13]; // Stores the channel that fsr 0-12 is playing on, if none then the value is 25
uint16_t settings[3]; // Stores slider and pot settings
bool vibrato;

uint32_t t1, t2, t3, t4;

int main() {
    stdio_init_all();
    synth_init();
    init_ch();
    adc_init();
    debounce_sw1_init();
    sw_in_init();
    vibrato = true;

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    t1 = timer_read();
    t3 = timer_read();
    while (1)
    {
        // Button Debounce Code
        t4 = timer_read();
        if (timer_elapsed_ms(t3, t4) >= DEBOUNCE_PD_MS)
        {
            debounce_sw1_tick();
            t3 = t4;
        }

        t2 = timer_read();
        if (timer_elapsed_ms(t1, t2) >= 500)
        {
            if (debounce_sw1_pressed()) {
                vibrato = !vibrato;
            }
            printf("%d\r", vibrato);
            set_vibrato(vibrato);
            slider_pot_read(settings);
            set_attack_decay(settings[1], settings[0]);
            set_sustain(settings[2]);
            t1 = t2;
        }

        fsr_read(fsr);
        for (uint8_t i = 0; i < 13; i++) {
            if (fsr[i] > 2000) {
                if (channel[i] != 25) {
                    play_note((enum Note) i, channel[i], 4, fsr[i]);
                } else {
                    for (uint8_t j = 0; j < 9; j++) {
                        if(playing[j] == false) {
                            playing [j] = true;
                            channel[i] = j;
                            play_note((enum Note) i, j, 4, fsr[i]);
                            break;
                        }
                    }
                }
            } else {
                if (channel[i] != 25) {
                    clear_note(channel[i]);
                    playing[channel[i]] = false;
                    channel[i] = 25;
                }
            }
        }
    }
}