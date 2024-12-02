/**
 * How to use WDT with clear
 * 
 * WDT started with 4 sec period and clear every 500ms. 
 * MCU not restarted and LED will blinking.  
 */
#include <wdt.h>

#include <delay.h>

#define LED P10

void main()
{
    wdt_init(0x06); //// 4.19 sec
    wdt_start();

    while (1) 
    {
        LED = !LED;
        delay_ms(500);

        wdt_clear();
    }
}