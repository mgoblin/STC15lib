/**
 * How to delay with timer0 in mode1
 */
#include <timer0_mode1.h>

#include <frequency.h>

#define LED P10

void main()
{
    set_frequency_divider_scale(4);

    timer0_mode1_1T_init();

    while(1)
    {
        timer0_mode1_delay(0xffff);
        LED = !LED;
    }
}