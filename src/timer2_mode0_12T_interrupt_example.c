#include <sys.h>
#include <bits.h>
#include <delay.h>
#include <timer.h>

#define LED P10

void timer2ISR() __interrupt(12)
{
    LED = !LED;
}

void main(void)
{
    timer2_mode0_12T_init();

    T2L = 0;
    T2H = 0;

    bit_set(AUXR, 4); // set T2 run flag

    delay_ms(2000);
}