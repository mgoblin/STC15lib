/**
 * Demonstrate how to enable timer2 as UART1 baud rate generator
 * 
 * After power on timer2 is UART1 baud rate generator and then swtich LED on for 3 sec.
 * LED off and disable timer2 as UART1 baud rate generator
 * In normal case LED will be off, if disabled operation failed then LED will be on 
 */
#include <timer2_mode0.h>

#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

void main()
{
    timer2_mode0_12T_init();

    if (is_timer2_mode0_as_uart1_baud_rate_enabled())
    {
        LED = ON;
        delay_ms(3000);
    }

    LED = OFF;

    enable_timer2_mode0_as_uart1_baud_rate(false);
    if (is_timer2_mode0_as_uart1_baud_rate_enabled())
    {
        LED = ON;
    }
    
    while (1)
    {
    }
    
}