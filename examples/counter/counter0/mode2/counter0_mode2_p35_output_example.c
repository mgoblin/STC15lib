/** 
 * How to enable and disable counter0 mode2 pin P3.5 output.
 * 
 * After counter0 overflow LED is blinks and P3.5 change it state.
 * At pin P3.5 meander signal generated.
 * 
 */
#include <counter0_mode2.h>

#include <delay.h>

#define LED P10
#define COUNTER_INITIAL_VALUE 240
#define COUNT_DELAY_MS 10

void timer0ISR(void) __interrupt(INTERRUPT_COUNTER0)
{
    LED = !LED;
}

void main()
{
    counter0_mode2_init();
    counter0_mode2_enable_P35_output();

    counter0_mode2_start(COUNTER_INITIAL_VALUE);

    while (1)
    {
        T0 = !T0;

        delay_ms(COUNT_DELAY_MS);
    }
    
}