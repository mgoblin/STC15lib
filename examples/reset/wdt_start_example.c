/** 
 * How to start Watch Dog Timer (WDT)
 * 
 * Start wdt once with 4 sec period. 
 * Then LED off, wait 2 sec and start blinking.
 * After 4 sec WDT restart MCU and LED if of on 2 sec 
 */
#include <reset.h>
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

void main()
{
    if (!is_wdt_started())
    {
        wdt_init(0x06); // 4.19 sec
        wdt_start();
    } 

    LED = OFF;
    delay_ms(2000);

    while (1) 
    {
        LED = ON;
        delay_ms(250);
        LED = OFF;
        delay_ms(250);
    }
}