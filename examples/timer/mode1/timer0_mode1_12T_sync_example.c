#include <sys.h>
#include <timer.h>

#include <stdint.h>

#define LED P10

void main()
{
    timer0_mode1_12T_init();

    while(1)
    {
        LED = !LED;
    }
}