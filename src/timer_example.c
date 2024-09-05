#include <sys.h>
#include <timer.h>

#include <stdint.h>

#define LED P10

void main()
{
    timer_mode0_init(TIMER1);
    
    while(1)
    {
        for(uint16_t i = 0; i < 2000; i++)
        {
            timer_mode0_run_and_wait(TIMER0, 0x1f, 0xff);
        }
        LED = !LED;
    }
}