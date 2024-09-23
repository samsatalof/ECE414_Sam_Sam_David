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
    Init,
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

uint32_t t1, t2, t3, t4;   // Timers for button debounce and game ticks
uint32_t gameTimer = 1000; // Tick timer for game varies between 100ms and 300ms.
uint8_t numberOfRoundsPlayed = 0;

uint32_t randValue;

char buff[256];

void tick()
{

    switch (PONG_State)
    {
    case Init:

        // Initialize currentPlayer with a random value.
        randValue = rand() % 2;
        if (randValue > 0)
        {
            currentPlayer = PlayerL;
            ledsStates = 0x80;
        }
        else
        {
            currentPlayer = PlayerR;
            ledsStates = 0x01;
        }
        led_out_write(ledsStates);
        printf("New round: %s serves\n", currentPlayer);
        printf("DEBUG: Round #%d", numberOfRoundsPlayed);

        PONG_State = Serve;
        ledsStatesCounter = 0;
        break;
    case Serve:
        printf("DEBUG: New tick, state is now: Serve\n"); // DEBUG ONLY LINE, Prints state machine state to UART console.

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
        printf("DEBUG: New tick, state is now: Travel\n"); // DEBUG ONLY LINE, Prints state machine state to UART console.
        // Check if the ball is at either of the extremes
        if (currentPlayer == PlayerL)
        {
            if (ledsStatesCounter < 7)
            {
                //ledsStates = ledsStates << 2;
                switch (ledsStatesCounter)
                {
                case 0:
                    ledsStates = 0x02;
                    break;
                case 1:
                    ledsStates = 0x04;
                    break;
                case 2:
                    ledsStates = 0x08;
                    break;
                case 3:
                    ledsStates = 0x10;
                    break;
                case 4:
                    ledsStates = 0x20;
                    break;
                case 5:
                    ledsStates = 0x40;
                    break;
                case 6:
                    ledsStates = 0x80;
                    break;
                default:
                    break;
                }

                led_out_write(ledsStates);
                ledsStatesCounter += 1;
            }
            else
            {
                PONG_State = Thwack;
            }
        }
        else // currentPlayer==PlayerR
        {
            if (ledsStatesCounter < 7)
            {
                //ledsStates = ledsStates >> 2;
                switch (ledsStatesCounter)
                {
                case 0:
                    ledsStates = 0x40;
                    break;
                case 1:
                    ledsStates = 0x20;
                    break;
                case 2:
                    ledsStates = 0x10;
                    break;
                case 3:
                    ledsStates = 0x08;
                    break;
                case 4:
                    ledsStates = 0x04;
                    break;
                case 5:
                    ledsStates = 0x02;
                    break;
                case 6:
                    ledsStates = 0x01;
                    break;
                default:
                    break;
                }
                led_out_write(ledsStates);
                ledsStatesCounter += 1;
            }
            else
            {
                PONG_State = Thwack;
            }
        }

        break;
    case Thwack:
        printf("DEBUG: New tick, state is now: Thwack\n"); // DEBUG ONLY LINE, Prints state machine state to UART console.

        if ((currentPlayer == PlayerL && debounce_sw1_pressed()))
        {
            currentPlayer = PlayerR;
            PONG_State = Travel;
        }
        else if ((currentPlayer == PlayerR && debounce_sw2_pressed()))
        {
            currentPlayer = PlayerL;
            PONG_State = Travel;
        }
        else
        {
            PONG_State = Victory;
        }
        ledsStatesCounter = 0;
        break;

    case Victory:
        printf("DEBUG: New tick, state is now: Victory\n"); // DEBUG ONLY LINE, Prints state machine state to UART console.

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
            // Output a message to the UART indicating which player lost.
            printf("Left player lost\n");
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
            // Output a message to the UART indicating which player lost.
            printf("Right player lost\n");
        }

        numberOfRoundsPlayed++;
        printf("DEBUG: Current Tick Speed is:%d\n", gameTimer);
        if (numberOfRoundsPlayed > 3)
        {
            printf("DEBUG: decreasing game tick speed to 200ms\n");
            gameTimer = 2000;
        }
        else if (numberOfRoundsPlayed > 5)
        {
            printf("DEBUG: decreasing game tick speed to 100ms\n");
            gameTimer = 1000;
        }
        PONG_State = Init;
        break;

    default:
        break;
    }
}

void initializeStuff()
{
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

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
    printf("Test that the UART WORKS BEFORE STATE MACHINE\n");
    // Set initial state for the state machine to begin:
    PONG_State = Init;
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
            tick();
            t3 = t4;
        }
    }
}