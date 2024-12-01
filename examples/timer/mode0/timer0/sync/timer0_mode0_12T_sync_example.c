/**
 * How to delay main program using timer0_mode0_delay on 12T timer closk divider 
 */
#include <timer0_mode0.h>

#define LED P10

void main()
{
    timer0_mode0_12T_init();

    while(1)
    {
        timer0_mode0_delay(0xffff);
        
        LED = !LED;
    }
}