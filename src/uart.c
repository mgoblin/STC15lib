#include <uart.h>


int putchar(int ch)
{
    uart1_send_byte(ch);
    return ch;
}

int getchar(void)
{
    uint8_t ch = 0;
	uart1_receive_byte(&ch);
	return ch;
}

