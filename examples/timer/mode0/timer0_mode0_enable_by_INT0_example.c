#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10
#define INT0 P32

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    INT0 = 0;

    /** 
     * This block of code doestn blink because INT0 = 0;
     */  
    timer0_mode0_12T_init();

    timer0_enable_on_pinINT0_high();

    timer0_mode0_start(0x00, 0x00);

    delay_ms(2000);

    timer0_mode0_stop();

    delay_ms(2000);
    //======================================================


    INT0 = 1;
    
    timer0_mode0_12T_init();

    timer0_enable_on_pinINT0_high();

    timer0_start(0xffff);

    delay_ms(2000);

    timer0_mode0_stop();

    delay_ms(2000);
}