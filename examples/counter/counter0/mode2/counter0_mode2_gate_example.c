/**
 *  How to enable/disable counter0 using gate
 * 
 *  LED should blink three times and off.
 */
#include <counter0_mode2.h>
#include <delay.h>

#define LED P10
#define COUNTER0_INIT_VALUE 240
#define LED_BLINKS_MAX_COUNT 3

uint16_t isr_calls_count = 0;

void counter0_ISR() __interrupt(1)
{
    if (isr_calls_count < (LED_BLINKS_MAX_COUNT << 1)) // Blink is equals to 2 LED state changes 
    {
        LED = !LED; // Change LED state to opposite
        isr_calls_count++;
    } else 
    {
        counter0_mode2_close_gate(); // gate is closed and counter is stopped
        LED = 1; // LED off
    }
}

void main()
{
    counter0_mode2_init(); // GATE = 0 counter0 enabled.
    counter0_mode2_start(COUNTER0_INIT_VALUE);
    
    while(1) {
        T0 = !T0;
        delay_ms(10);
    }
}