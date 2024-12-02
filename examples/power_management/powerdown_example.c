/** 
 * How to use power_down mode with wakeup timer
 */
#include <power_management.h>

#include <interrupt.h>
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

void delay(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
    delay(250);
    LED = ON;
    
    delay(250);
    LED = OFF;
    
    WKTCL = 0xff;
    WKTCH = 0x9f;

    power_down();
}