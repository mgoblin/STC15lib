/**
 * How to use direct reload
 */

#include <timer0_mode0.h>

#include <delay.h>

#define LED P10
#define VALUES_SIZE 3

const uint8_t TL0_values[VALUES_SIZE] = { 0xff, 0xff, 0xff };
const uint8_t TH0_values[VALUES_SIZE] = { 0x10, 0x80, 0xef };

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    set_frequency_divider_scale(3);

    timer0_mode0_12T_init();
    timer0_mode0_start(0xffff);

    while (1)
    {
        for (uint8_t i = 0; i < VALUES_SIZE; i++)
        {
            timer0_mode0_direct_reload(TH0_values[i], TL0_values[i]);
            delay_ms(3000);
        }
    }
    
}