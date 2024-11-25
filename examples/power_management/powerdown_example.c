#include <power_management.h>

#include <reset.h>
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
    if (!is_wdt_started())
    {
        wdt_init(5); // 4 sec
        wdt_start();
    }
    else
    {
        reset_wdt_flag();
    }

    while (1)
    {
        delay(250);
        wdt_clear();
        LED = ON;
        
        delay(250);
        wdt_clear();
        LED = OFF;

        wdt_clear();

        power_down();
    }
    
}