/**
 * Demostrate reloading timer0 on the fly.
 * ticks array contains timer ticks series that cyclic rotates 
 * with timer0_reload call after timer start.
 */
#include <timer0_mode3.h>
#include <delay.h>

#define LED P10
#define TICKS_ARRAY_SIZE 3

const uint16_t ticks[TICKS_ARRAY_SIZE] = {0xffff, 0x7FFF, 0x3FFF};

static 
void main()
{
    set_frequency_divider_scale(2);

    timer0_mode3_12T_init();
    timer0_mode3_start(ticks[0]);

    while (1)
    {
        for(uint8_t idx = 0; idx < TICKS_ARRAY_SIZE; idx++)
        {
            timer0_mode3_reload(ticks[idx]);
            delay_ms((TICKS_ARRAY_SIZE - idx) * 1000);
        }
    }
}

void timerISR() __interrupt(1)
{
    LED = !LED;
}