#include <sys.h>
#include <bits.h>
#include <delay.h>

#define LED P10

void timer2ISR() __interrupt(12) __using(1)
{
    LED = !LED;
}

void main(void)
{
    EA = 1; // all interrupts enabled
    bit_clr(AUXR, 4); // clear T2 run flag
    bit_clr(AUXR, 3);
    bit_clr(AUXR, 2);

    T2L = 0;
    T2H = 0;

    IE2 |= 0x04;

    bit_set(AUXR, 4); // set T2 run flag

    delay_ms(2000);
}