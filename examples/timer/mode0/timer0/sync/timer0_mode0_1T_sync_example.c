/**
 * How to delay main program using timer0_mode0_delay on 1T timer closk divider 
 */
#include <timer0_mode0.h>

#define LED P10

void main()
{
    timer0_mode0_1T_init();

    while(1)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            timer0_mode0_delay(0xffff);
        }
        LED = !LED;
    }
}