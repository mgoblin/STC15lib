/**
 * This is an example of how to use uart1 in mode2.
 * 
 * baudrate = 345600
 * 8 bits - Odd parity - 1 stop bit
 * 
 * Send Y to uart1 and delay 500 ms
 * In UART1 ISR handler LED will be turned on after transmission is complete
 * 
 */
#include <uart1_mode2.h>
#include <delay.h>

#define LED P10

void uart1ISR() __interrupt(4)
{
    if(TI)
    {
        LED = 0;
    }
}

void main()
{
    uart1_mode2_init(RxD_P30_TxD_P31, baudrate_345600);
	
    while(1)
    {
        LED = 1;
        uart1_send_byte_odd_parity('Y');
        delay_ms(500);
    }
}
