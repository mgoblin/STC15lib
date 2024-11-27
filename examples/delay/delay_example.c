/**
 * How to use edelay_ms example.
 * 
 * Blink LED 500 ms with to mcu frequency slowdown adaption.
 */
#include <sys.h>
#include <delay.h>

#define LED P10

void main()
{
    set_frequency_divider_scale(2);
    
    while (1)
    {
        LED = !LED;
        delay_ms(500);
    }
}