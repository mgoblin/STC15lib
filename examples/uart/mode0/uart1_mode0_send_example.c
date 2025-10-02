/**
 * This is an example of how to use uart1 in mode0.
 * 
 * Send 0x75 to uart1 and delay 1ms
 * 
 * RxD and TxD pins state diagram are pictured at 
 * @image html UART1_mode0.png
 */
#include <uart1_mode0.h>
#include <delay.h>

void main()
{
	uart1_mode0_init(baudrate_921600);
	
    while(1)
    {
        uart1_send_byte(0x75);
        delay_ms(1);
    }
}
