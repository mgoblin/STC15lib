/**
 * How to handle timer2 interrupts
 */
#include <timer2_mode0.h>
#include <frequency.h>

#define LED P10

// Timer2 raise interrupt 12 afer overflow. This is an interrupt handler.
void timer2ISR() __interrupt(12)
{
    LED = !LED;
}

void main(void)
{
    set_frequency_divider_scale(7);
    
    timer2_mode0_1T_init();
    timer2_mode0_start(0xffff);

    while(1) {}
}