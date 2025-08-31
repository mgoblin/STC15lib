/**
 * How to delay with timer0 in mode2
 */
#include <timer0_mode2.h>

#define LED P10

void main()
{
    timer0_mode2_12T_init();
    
    while(1)
    {
        for(uint16_t i = 0; i < 1000; i++)
        {
            timer0_mode2_delay(0xff);
        }
        LED = !LED;
    }
}