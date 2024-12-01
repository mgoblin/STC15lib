/**
 * Demostrate reloading timer0 on the fly.
 * 
 * Ticks array contains timer ticks series that cyclic rotates 
 * and timer0_reload call change timings on the fly.
 * 
 * LED should blinks more and more faster
 */
#include <timer0_mode0.h>
#include <delay.h>

#define LED P10
#define TICKS_ARRAY_SIZE 4

const uint16_t ticks[TICKS_ARRAY_SIZE] = {0xFFFF, 0x7FFF, 0x3FFF, 0x0FFF};

void main()
{
    set_frequency_divider_scale(2);

    timer0_mode0_12T_init();
    timer0_mode0_start(ticks[0]);

    while (1)
    {
        for(uint8_t idx = 0; idx < TICKS_ARRAY_SIZE; idx++)
        {
            timer0_mode0_reload(ticks[idx]);
            delay_ms((TICKS_ARRAY_SIZE - idx) * 1000);
        }
    }
}

void timerISR() __interrupt(1)
{
    LED = !LED;
}