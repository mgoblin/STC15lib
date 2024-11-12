#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
    delay_ms(500);
}

void main()
{
    timer0_mode2_12T_init();

    // LED blinking during 1 second 
    timer0_start(0xff00);
}