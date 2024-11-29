/** 
 * How to start Watch Dog Timer (WDT)
 * 
 * Start wdt with 4 sec period. 
 * Then LED off, wait 3 sec and start blinking.
 * After 4 sec WDT restart MCU to first main instruction and LED if of/on ~1 sec (3 times led on)
 */
#include <wdt.h>
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

void delay(uint16_t ms);

void main()
{
    wdt_init(0x06); // 4.19 sec
    wdt_start();

    delay(3000);

    while (1) 
    {
        LED = !LED;
        delay(250);
    }
}

void delay(uint16_t ms)
{
    delay_ms(ms);
}