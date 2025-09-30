#include <uart.h>

void uart1_send_byte(uint8_t data)
{
    SBUF = data;
	while(!TI);
	TI=0;
}

uint8_t uart1_receive_byte()
{
	while(!RI);
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

