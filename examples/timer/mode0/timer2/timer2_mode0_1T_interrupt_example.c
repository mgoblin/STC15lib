#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10

void timer2ISR() __interrupt(12)
{
    LED = !LED;
}

void main(void)
{
    timer2_mode0_1T_init();

    timer2_mode0_start(0xffff);

    while(1) {}

}