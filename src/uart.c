#include <uart.h>

void uart1_init(uint32_t uart_baudrate)
{
    SCON = 0x50; // Set Mode1: 8-Bit UART with Variable Baud Rate
    
    timer2_mode0_1T_init(); 
    enable_timer2_mode0_as_uart1_baud_rate(true);
    
    //======== change by timer2 aux calc and timer2_mode0_start() ======

    T2L = (65536 - (MAIN_Fosc/4/uart_baudrate)); //Set the preload value
    T2H = (65536 - (MAIN_Fosc/4/uart_baudrate))>>8;

    bit_set(AUXR, 4); // run timer2

    //======== change by timer2 aux calc and timer2_mode0_start() ======
}

void uart1_send_byte(uint8_t data)
{
    SBUF = data;
	while(TI==0);
	TI=0;
}

uint8_t uart1_receive_byte()
{
	while(RI==0);
	RI=0;
	return(SBUF);
}

int putchar(int ch)
{
    uart1_send_byte(ch);
    return ch;
}

int getchar(void)
{
    return uart1_receive_byte();
}

