/**
 * delay_ms example
 * blink LED 500 ms and adapt to mcu frequency slowdown
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