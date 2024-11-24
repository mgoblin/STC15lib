/**
 * How to use WDT with clear
 * 
 * WDT started with 4 sec periaod and clear every second. 
 * MCU not restarted and after 5 sec delay on start LED is blinking.  
 * 
 */
#include <reset.h>

#include <delay.h>

#define LED P10

void main()
{
    if (!is_wdt_started())
    {
        wdt_init(0x06); //// 4.19 sec
        wdt_start();
    }

    delay_ms(5000);
    
    while (1) 
    {
        LED = !LED;
        delay_ms(1000);

        wdt_clear();
    }
}