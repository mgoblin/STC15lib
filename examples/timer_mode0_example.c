#include <sys.h>
#include <timer.h>

#include <stdint.h>

#define LED P10

void main()
{
    timer_mode0_init(TIMER1);
    
    while(1)
    {
        timer_mode0_run_and_wait(TIMER0, 0x00, 0x00);
        LED = !LED;
    }
}