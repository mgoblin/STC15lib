/**
 * How to read and reset WDT flag
 * 
 * Start WDT with 4 sec overflow time 
 * 
 * Then print to UART WDT flag value - 0 every 1 sec.
 * After WDT reset MCU print to UART WDT flag 1 and clear flag
 * 
 * After WDT reset UART output will be 1, 0, 0, 0..
 */
#include <wdt.h>

#include <delay.h>
#include <uart.h>
#include <stdio.h>

void main()
{
    uart1_init(9600);

    printf_tiny("WDT flag is %d\r\n", is_wdt_flag_on());
    wdt_flag_reset();

    wdt_init(0x05);
    wdt_start();
    while(1)
    {
        printf_tiny("WDT flag is %d\r\n", is_wdt_flag_on());
        delay_ms(1000);
    }
}