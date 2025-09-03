#include <counter0_mode0.h>
#include <delay.h>

#define LED P10
#define COUNTER_INIT_VALUE 65505U // Initial counter value

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    counter0_mode0_init();
    counter0_mode0_start(COUNTER_INIT_VALUE);
    counter0_mode0_enable_P35_output();

    while (1)
    {
        T0 = !T0;
        delay_ms(10);
    }
    
}