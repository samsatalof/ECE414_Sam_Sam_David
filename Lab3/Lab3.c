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
    Player1,
    Player2
} currentPlayer;
bool button = true;
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
            currentPlayer = Player1;
        }
        else
        {
            currentPlayer = Player2;
        }
        // Serve the ball from the current player.
        if (currentPlayer == Player1)
        {
            // Check Switch, if switchin, move to travel
            if (debounce_sw1_pressed())
            {
                t2 = timer_read();
            }
            if (currentPlayer == Player1)
            {
                currentPlayer == Player2;
            }
            else
            {
                currentPlayer == Player1;
            }
        }
        else
        {
            PONG_State = Travel;
        }
        break;
    case Travel:
    //Check if the ball is at either of the extremes
    if (){
    } else {
        //Continue moving the ball across the field
        //CALL THE FOR LOOP with the bitshifts here
        
    }
    
        break;
    case Thwack:

        break;

    case Victory:

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