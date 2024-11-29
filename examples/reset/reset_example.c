/**
 * How to software reset MCU
 * 
 * Without reset call this example do LED blinking.
 * But reset doesnt execute blink code in while cycle and as a result LED not blinking.
 */
#include <reset.h>
#include <delay.h>

#define LED P10
void main()
{
    reset();

    while (1)
    {
        LED = !LED;
        delay_ms(500);
    }
    
}