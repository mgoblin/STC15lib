#include <sys.h>
#include <timer.h>

#include <stdint.h>

#define LED P10

void main()
{
    timer0_mode0_12T_init();

    while(1)
    {
        timer0_mode0_run_once_and_wait(0x00, 0x00);
        LED = !LED;
    }
}