/**
 * This is an example of how chage the baud rate of uart1 in mode0.
 * 
 * Send 0x75 to uart1 on Sysclk/12 and Sysclk/2 baud rates.
 * 
 * RxD and TxD pins state diagram are pictured at 
 * @image html UART1_mode0_clk.png
 */
#include <uart1_mode0.h>
#include <delay.h>

void send_byte(uint8_t byte) __naked
{
    uart1_mode0_send_byte(byte);
    __asm ret __endasm;
}

void main()
{
	while(1)   {
        
        uart1_mode0_init(UART_BaudRate_921600);
        send_byte(0x75);
        
        uart1_mode0_init(UART_BaudRate_5529600);
        send_byte(0x75);
        
        delay_ms(1);
    }
}
