#include<sys.h>
#include <timer.h>

#include<delay.h>

#define LED P10
#define INT0 P32

void timer0ISR(void) __interrupt(1)
{
    LED = 1;
}

void main()
{
    timer0_mode0_12T_init();
    timer0_enable_on_pinINT0_high();

    timer0_mode0_start(0xff, 0xff);

    while (1)
    {
        INT0 = 0;
        LED = 0;
        delay_ms(1000);
        
        INT0 = 1;
        delay_ms(1000);
    }
}