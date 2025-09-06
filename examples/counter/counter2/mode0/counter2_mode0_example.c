/**
 * How to use counter2 in mode0.
 * 
 * This example configures counter2 to count from COUNTER_INIT_VALUE
 * to 65535 (100 counts).
 * Pin T2 used as an input for counter0. 
 * 
 * After init T2 programmatically changed.
 * After counter overflow LED is changing it state.  
 */
#include <counter2_mode0.h>
#include <pin.h>

#include <delay.h>


#define LED P10
#define COUNTER_INIT_VALUE 65435U // Initial counter value

void timer2ISR(void) __interrupt(12)
{
    LED = !LED;
}

void main()
{
    counter2_mode0_init();
    counter2_mode0_start(COUNTER_INIT_VALUE);
    
    pin_quasi_bidiretional_init(P3, 4);

    while (1) {
        T2 = !T2;
        delay_ms(50);
    }
}