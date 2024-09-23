#include "pico/stdlib.h"
#include "sw_in.h"
#include <stdint.h>
#include <stdlib.h>
#include "led_out.h"
#include <stdbool.h>
#include "timer.h"
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_ID uart0
#define BAUD_RATE 115200
// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1


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

uint32_t t1, t2, t3, t4;  // Timers for button debounce and game ticks
uint32_t gameTimer = 300; // Tick timer for game varies between 100ms and 300ms.
uint8_t numberOfRoundsPlayed = 0;

uint32_t randValue;

char buff[256];

void tick()
{
    // sprintf("DEBUG: New tick, state is now: %s \n", PONG_State);
    uart_puts(UART_ID, buff); // DEBUG ONLY LINE, Prints state machine state to UART console.
    switch (PONG_State)
    {
    case Serve:
        // Initialize currentPlayer with a random value.
        randValue = rand() % 2;
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
        // uart_puts(UART_ID, sprintf("New round: %s serves\n", currentPlayer));
        // uart_puts(UART_ID, sprintf("DEBUG: Round #%d", numberOfRoundsPlayed));

        // Serve the ball from the current player.
        if (currentPlayer == PlayerL)
        {
            // Check Switch, if switching, move to travel
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
                else if (ledsStates == 0x80)
                {
                    ledsStates = 0x00;
                }
                else
                {
                    ledsStates = 0x80;
                }
                led_out_write(ledsStates);
            }
        }
        else if (currentPlayer == PlayerR)
        {
            // Flash the LED
            // counter
            if (victoryPulse < 5)
            {
                victoryPulse += 1;
                if (ledsStates == 0x80)
                {
                    ledsStates = 0x01;
                }
                else if (ledsStates == 0x00)
                {
                    ledsStates = 0x01;
                }
                else
                {
                    ledsStates = 0x00;
                }
                led_out_write(ledsStates);
            }
        }
        // Output a message to the UART indicating which player lost.
        // uart_puts(UART_ID, sprintf("Player %s lost\n", currentPlayer));
        numberOfRoundsPlayed++;
        // uart_puts(UART_ID, sprintf("DEBUG: Current Tick Speed is:%d", gameTimer));
        if (numberOfRoundsPlayed > 3)
        {
            // uart_puts(UART_ID, sprintf("DEBUG: decreasing game tick speed to 200ms"));
            gameTimer = 200;
        }
        else if (numberOfRoundsPlayed > 5)
        {
            // uart_puts(UART_ID, sprintf("DEBUG: decreasing game tick speed to 100ms"));
            gameTimer = 100;
        }
        break;

    default:
        break;
    }
}

void initializeStuff()
{
    stdio_init_all();
    led_out_init();
    sw_in_init();
    debounce_sw1_init();
    debounce_sw2_init();
    t1 = timer_read();
    t3 = timer_read();
}

int main()
{
    initializeStuff();
    uart_puts(UART_ID, "AHAHAHAHAHAHGAHGAGHAGH!!!\n");
    while (1)
    {
        // Button Debounce Code
        t2 = timer_read();
        if (timer_elapsed_ms(t1, t2) >= DEBOUNCE_PD_MS)
        {
            debounce_sw1_tick();
            debounce_sw2_tick();
            t1 = t2;
        }
        // Tick the game state machine.
        t4 = timer_read();
        if (timer_elapsed_ms(t3, t4) >= gameTimer)
        {
            debounce_sw1_tick();
            debounce_sw2_tick();
            t3 = t4;
        }
    }
}