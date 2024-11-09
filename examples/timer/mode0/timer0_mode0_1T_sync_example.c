#include <sys.h>
#include <timer.h>

#include <stdint.h>

#define LED P10

void main()
{
    timer0_mode0_1T_init();

    while(1)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            timer0_mode0_run_once_and_wait(0x00);
        }
        LED = !LED;
    }
}