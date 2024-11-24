/**
 * How to read and reset WDT flag
 * 
 * Start WDT with 4 sec 
 * 
 * Then print to UART WDT flag value - 0 every 1 sec.
 * After WDT reset MCU print to UART WDT flag 1 and clear flag
 * 
 * UART output will 0, 0, 0, 0, 1 in period
 */
#include <reset.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

void main()
{
    if (!is_wdt_started())
    {
        wdt_init(0x06); //// 4.19 sec
        wdt_start();
    }
    
    uart1_init(9600);
    while (1) 
    {
        printf_tiny("WDT flag is %d\n", is_wdt_flag_on());
        
        if (is_wdt_flag_on())
        {
            reset_wdt_flag();
        }
        
        delay_ms(1000);
    }
}