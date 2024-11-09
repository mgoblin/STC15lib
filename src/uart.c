#include <uart.h>

void uart_init(uint32_t uart_baudrate)
{
    SCON = 0x50; // Set Mode1: 8-Bit UART with Variable Baud Rate 
    T2L = (65536 - (MAIN_Fosc/4/uart_baudrate)); //Set the preload value
    T2H = (65536 - (MAIN_Fosc/4/uart_baudrate))>>8;
    AUXR = 0x14; //T2 in 1T mode, and run T2
    AUXR |= 0x01; 
}

void uart_send_byte(uint8_t data)
{
    SBUF = data;
	while(TI==0);
	TI=0;
}

uint8_t uart_receive_byte()
{
	while(RI==0);
	RI=0;
	return(SBUF);
}

int putchar(int ch)
{
    uart_send_byte(ch);
    return ch;
}

int getchar(void)
{
    return uart_receive_byte();
}

