/** 
 * How to start Watch Dog Timer (WDT)
 * 
 * Start wdt once with 4 sec period. 
 * Then LED off, wait 3 sec and start blinking.
 * After 4 sec WDT restart MCU and LED if of/on 1 sec (3 times led on)
 */
#include <reset.h>
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

void main()
{
    wdt_init(0x06); // 4.19 sec
    wdt_start();

    LED = OFF;
    delay_ms(3000);

    while (1) 
    {
        LED = ON;
        delay_ms(250);
        LED = OFF;
        delay_ms(250);
    }
}