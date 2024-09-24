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

// FSM States:
enum PONG_States
{
    Init,
    Serve,
    Travel,
    Thwack,
    Victory
} PONG_State;

// Player enum:
enum currentPlayer
{
    PlayerL, // LEFT PLAYER
    PlayerR  // RIGHT PLAYER
} currentPlayer;

uint8_t ledsStates = 0;        // 8-bit value to write to the LEDs, using 1 for the FSM saves memory and can make things easier to keep track of
uint8_t ledsStatesCounter = 0; // Counter for multi-tick actions, ex. LED flash and travel, using 1 for the same reasons as ledsStates

uint32_t t1, t2, t3, t4;          // Timers for button debounce and game ticks
uint32_t gameTimer = 300;         // Tick timer for game varies between 100ms and 300ms.
uint8_t numberOfRoundsPlayed = 0; // Keeps track of rounds played to update gameTimer

uint32_t randValue;

void tick()
{

    switch (PONG_State)
    {
    case Init:

        // printf("Entering Init state"); // Test T4

        // Randomize initial player
        randValue = rand() % 2;
        if (randValue > 0)
        {
            currentPlayer = PlayerL;
            ledsStates = 0x80;
            printf("Left Player Serves");
        }
        else
        {
            currentPlayer = PlayerR;
            ledsStates = 0x01;
            printf("Right Player Serves");
        }

        led_out_write(ledsStates); // Writes to the initial LED indicating serving player
        PONG_State = Serve;        // Moves to Serve
        ledsStatesCounter = 0;     // Resets the counter used to flash/travel the LEDs

        break;
    case Serve:
        // printf("New tick, state is now: Serve\n"); // DEBUG ONLY LINE, Test T4

        // Serve the ball from the current player.
        if (currentPlayer == PlayerL)
        {
            // Check if player has served, if so then swap players and switch to Travel
            if (debounce_sw1_pressed())
            {
                currentPlayer = PlayerR;
                PONG_State = Travel;
            }
        }
        else
        {
            // Check Switch, if switchin, move to travel
            if (debounce_sw2_pressed())
            {
                currentPlayer = PlayerL;
                PONG_State = Travel;
            }
        }
        break;
    case Travel:
        // printf("New tick, state is now: Travel\n"); // DEBUG ONLY LINE, Test T4

        // Check if the ball is at either of the extremes
        if (currentPlayer == PlayerL)
        {
            if (ledsStatesCounter < 7)
            {
                ledsStates = ledsStates << 1;
                led_out_write(ledsStates);
                ledsStatesCounter += 1;
            }
            else
            {
                PONG_State = Thwack;
                ledsStatesCounter = 0;
            }
        }
        else // currentPlayer==PlayerR
        {
            if (ledsStatesCounter < 7)
            {
                ledsStates = ledsStates >> 1;
                led_out_write(ledsStates);
                ledsStatesCounter += 1;
            }
            else
            {
                PONG_State = Thwack;
                ledsStatesCounter = 0;
            }
        }

        break;
    case Thwack:
        // printf("New tick, state is now: Thwack\n"); // DEBUG ONLY LINE, Test T4

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
        break;

    case Victory:
        // printf("New tick, state is now: Victory\n"); // DEBUG ONLY LINE, Test T4

        if (currentPlayer == PlayerL)
        {
            // Flash the LED of the winning side
            if (ledsStatesCounter < 5)
            {
                ledsStatesCounter += 1;
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
            else
            {
                // Output a message to the UART indicating which player lost.
                printf("Left player lost\n");
                // Switch to Init state and reset the used counter
                PONG_State = Init;
                ledsStatesCounter = 0;
            }
        }
        else if (currentPlayer == PlayerR)
        {
            // Flash the LED of the winning side
            if (ledsStatesCounter < 5)
            {
                ledsStatesCounter += 1;
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
            else
            {
                // Output a message to the UART indicating which player lost.
                printf("Right player lost\n");
                // Switch to Init state and reset the used counter
                PONG_State = Init;
                ledsStatesCounter = 0;
            }
        }

        numberOfRoundsPlayed++;
        printf("DEBUG: Current Tick Speed is:%d\n", gameTimer);
        if (numberOfRoundsPlayed > 3)
        {
            printf("DEBUG: decreasing game tick speed to 200ms\n");
            gameTimer = 200;
        }
        else if (numberOfRoundsPlayed > 5)
        {
            printf("DEBUG: decreasing game tick speed to 100ms\n");
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