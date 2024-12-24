/**
 * Demostrate reloading timer2 on the fly.
 * ticks array contains timer ticks series that cyclic rotates 
 * with timer0_reload call after timer start.
 */
#include <timer2_mode0.h>
#include <delay.h>
#include <frequency.h>

#define LED P10
#define TICKS_ARRAY_SIZE 3

const uint16_t ticks[TICKS_ARRAY_SIZE] = {0xFFFF, 0x07FFF, 0x03FFF};

void main()
{
    set_frequency_divider_scale(2);

    timer2_mode0_12T_init();
    timer2_mode0_start(ticks[0]);

    while (1)
    {
        for(uint8_t idx = 0; idx < TICKS_ARRAY_SIZE; idx++)
        {
            timer2_mode0_reload(ticks[idx]);
            LED = 1; // LED Off
            delay_ms((TICKS_ARRAY_SIZE - idx) * 1000);
        }
    }
}

void timerISR() __interrupt(12)
{
    LED = !LED;
}