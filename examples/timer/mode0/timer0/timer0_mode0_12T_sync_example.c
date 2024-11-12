#include <sys.h>
#include <timer0_mode0.h>

#include <stdint.h>

#define LED P10
#define TIMER_CYCLES_MULTIPLIER 10

void main()
{
    timer0_mode0_12T_init();

    while(1)
    {
        for(uint8_t i = 0; i < TIMER_CYCLES_MULTIPLIER; i++) {
            timer0_mode0_run_once_and_wait(0xffff);
        }
        
        LED = !LED;
    }
}