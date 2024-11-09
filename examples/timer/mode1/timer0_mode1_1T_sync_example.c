#include <sys.h>
#include <timer.h>

#include <stdint.h>

#define LED P10
#define TIMER_CYCLES_MULTIPLIER 10

void main()
{
    timer0_mode1_1T_init();

    while(1)
    {
        for(uint8_t i = 0; i < 12 * TIMER_CYCLES_MULTIPLIER; i++) {
            timer0_mode1_run_once_and_wait(0x00, 0x00); // 0, 0 take maximal timer delay
        }
        
        LED = !LED;
    }
}