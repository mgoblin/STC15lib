/**
 * How to use delay with timer0 in mode3
 */
#include <timer0_mode3.h>
#include <frequency.h>

#define LED P10

void main()
{
    set_frequency_divider_scale(1);

    timer0_mode3_12T_init();

    while(1)
    {
        timer0_mode3_delay(0xffff);
        LED = !LED;
    }
}