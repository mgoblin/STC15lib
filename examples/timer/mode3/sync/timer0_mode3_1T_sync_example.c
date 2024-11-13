#include <sys.h>
#include <timer0_mode3.h>

#include <stdint.h>

#define LED P10

void main()
{
    timer0_mode3_1T_init();

    while(1)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            timer0_mode3_delay(0xffff);
        }
        LED = !LED;
    }
}