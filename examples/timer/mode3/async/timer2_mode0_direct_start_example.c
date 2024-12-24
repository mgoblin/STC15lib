/**
 * How to start timer2 in mode0 with direct set of TH0 and TL0
 */

#include <timer2_mode0.h>
#include <frequency.h>

#define LED P10


void timerISR() __interrupt(12)
{
    LED = !LED;
}

void main()
{
    set_frequency_divider_scale(2);

    timer2_mode0_12T_init();
    timer2_mode0_direct_start(0x00, 0x00);

    while (1)
    {
    }
}