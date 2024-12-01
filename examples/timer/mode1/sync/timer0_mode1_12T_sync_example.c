/** 
 * How to delay with timer0 in mode1
 */
#include <timer0_mode1.h>

#define LED P10

void main()
{
    timer0_mode1_12T_init();

    while(1)
    {
        timer0_mode1_delay(0xffff);
        
        LED = !LED;
    }
}