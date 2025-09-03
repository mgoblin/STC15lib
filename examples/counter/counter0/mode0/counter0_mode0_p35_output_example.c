/** 
 * How to enable and disable counter0 mode0 pin P3.5 output.
 * 
 * Counter0 start counting from COUNTER_INIT_VALUE to 65535.
 * 
 * After counter0 overflow LED is blinks and P3.5 change it state.
 * At pin P3.5 meander signal generated.
 * 
 */
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