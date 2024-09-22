#include "pico/stdlib.h"
#include "sw_in.h"
#include <stdint.h>
#include <stdlib.h>
#include "led_out.h"
#include <stdbool.h>
#include "timer.h"
#include "debounce_sw1.h"
#include "debounce_sw2.h"

enum PONG_States
{
    Serve,
    Travel,
    Thwack,
    Victory
} PONG_State;

enum currentPlayer
{
    PlayerL, // LEFT PLAYER
    PlayerR  // RIGHT PLAYER
} currentPlayer;

bool button = true;
uint8_t ledsStates = 0;
uint8_t ledsStatesCounter = 0;

uint8_t victoryPulse = 0;

uint32_t t1, t2; //
void tick()
{
    switch (PONG_State)
    {
    case Serve:
        // Initialize currentPlayer with a random value.
        uint32_t randValue = rand() % 2;
        if (randValue > 0)
        {
            currentPlayer = PlayerL;
            ledsStates = 0x01;
        }
        else
        {
            currentPlayer = PlayerR;
            ledsStates = 0x80;
        }
        led_out_write(ledsStates);

        // Serve the ball from the current player.
        if (currentPlayer == PlayerL)
        {
            // Check Switch, if switchin, move to travel
            if (debounce_sw1_pressed())
            {
                t2 = timer_read();
                currentPlayer = PlayerR;
                PONG_State = Travel;
            }
        }
        else
        {
            // Check Switch, if switchin, move to travel
            if (debounce_sw2_pressed())
            {
                t2 = timer_read();
                currentPlayer = PlayerL;
                PONG_State = Travel;
            }
        }
        break;
    case Travel:
        // Check if the ball is at either of the extremes
        if (currentPlayer == PlayerL)
        {
            if (ledsStatesCounter < 7)
            {
                ledsStatesCounter += 1;
                ledsStates << 1;
            }
            else
            {
                PONG_State = Thwack;
            }
        }
        else // currentPlayer==PlayerR
        {
            ledsStatesCounter += 1;
            ledsStates >> 1;
            // Continue moving the ball across the field
        }

        break;
    case Thwack:

        if ((currentPlayer == PlayerL && debounce_sw2_pressed()))
        {
            currentPlayer = PlayerR;
        }
        else if ((currentPlayer == PlayerR && debounce_sw1_pressed()))
        {
            currentPlayer = PlayerL;
        }
        else
        {
            PONG_State = Victory;
        }

        break;

    case Victory:
        // Flash the LED nearest the winning player and switch to serve.
        if (currentPlayer == PlayerL)
        {
            // Flash the LED
            // counter
            if (victoryPulse < 5)
            {
                victoryPulse += 1;
                if (ledsStates == 0x01)
                {
                    ledsStates = 0x80;
                }
                else if(ledsStates == 0x80)
                {
                    ledsStates = 0x00;
                } else {
                    ledsStates = 0x80;
                }
                led_out_write(ledsStates);
            }
        }
        // Output a message to the UART indicating which player lost.

        break;

    default:
        break;
    }
}

int main()
{
    sw_in_init();
    debounce_sw1_init();
    t1 = timer_read();
    stdio_init_all();

    while (1)
    {
        tick();
        if (timer_elapsed_ms(t1, t2) >= DEBOUNCE_PD_MS)
        {
            debounce_sw1_tick();
            t1 = t2;
        }
    }
}