#include <timer0_mode2.h>

#define LED P10
#define TIMER_CYCLES_MULTIPLIER 1000

void main()
{
    timer0_mode2_12T_init();

    while(1)
    {
        for(uint16_t i = 0; i < TIMER_CYCLES_MULTIPLIER; i++) {
            timer0_mode2_delay(0xff);
        }
        
        LED = !LED;
    }
}