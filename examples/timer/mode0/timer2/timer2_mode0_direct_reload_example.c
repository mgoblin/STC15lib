/**
 * Demostrate direct reloading timer2 T2H and T2L registers on the fly.
 */
#include <timer2_mode0.h>
#include <delay.h>
#include <frequency.h>

#define LED P10

#define TICKS_ARRAY_SIZE 3
const uint8_t T2H_values[TICKS_ARRAY_SIZE] = { 0x10, 0x80, 0xef };
const uint8_t T2L_values[TICKS_ARRAY_SIZE] = { 0xFF, 0xFF, 0x0FF };

void main()
{
    set_frequency_divider_scale(3);

    timer2_mode0_12T_init();
    timer2_mode0_start(0xFFFF);

    while (1)
    {
        for(uint8_t idx = 0; idx < TICKS_ARRAY_SIZE; idx++)
        {
            timer2_mode0_direct_reload(T2H_values[idx], T2L_values[idx]);
            delay_ms(3000);
        }
    }
}

void timerISR() __interrupt(12)
{
    LED = !LED;
}