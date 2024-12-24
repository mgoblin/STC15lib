/**
 * How to directly reload timer0 register value on the fly.
 * 
 * After power on LED blinking with increase frequency
 */
#include <timer0_mode2.h>
#include <frequency.h>
#include <delay.h>


#define LED P10 // LED pin

#define BLINKS 10 // Blink every BLINKS in timer interrupt handler
uint8_t blink_divider = 0; // timer interrupt counter

// Timer0 values array with blinking frequencies
#define VALUES_SIZE 3
const uint8_t timer_values[VALUES_SIZE] = { 0xd0, 0x70, 0x00 };

void timerISR() __interrupt(1)
{
    if (blink_divider >= BLINKS)
    {
        blink_divider = 0;
        LED = !LED;
    }
    else 
    {
        blink_divider++;
    }
} 

void main()
{
    set_frequency_divider_scale(7);

    timer0_mode2_12T_init(); 
    timer0_mode2_start(0xff);

    while (1)
    {
        for (uint8_t i = 0; i < VALUES_SIZE; i++)
        {
            timer0_mode2_direct_reload(timer_values[i]);
            delay_ms(2000);
        }
    }
}