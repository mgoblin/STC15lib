/**
 * This is an example of how to use uart1 in mode2.
 * 
 * baudrate = 345600
 * 8 bits - Odd parity - 1 stop bit
 * 
 * Echo received data
 * 
 */
#include <uart1_mode2.h>

#define LED P10

void main()
{
    uint8_t received_byte;
    uart1_mode2_init(RxD_P30_TxD_P31, baudrate_345600);
	
    LED = 1; // LED off
    
    while(1)
    {
        LED = 0; // LED on
        // Waiting for data received
        uart1_receive_byte_even_parity(received_byte);
        
        LED = 1; // LED off
        uart1_send_byte_even_parity(received_byte);
        uart1_send_byte_even_parity('\r');
        uart1_send_byte_even_parity('\n');
    }
}
