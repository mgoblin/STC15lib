#include <uart.h>

uint16_t uart1_init(uint16_t uart_baudrate)
{
    SCON = 0x50; // Set Mode1: 8-Bit UART with Variable Baud Rate
    
    timer2_mode0_1T_init(); 
    enable_timer2_mode0_as_uart1_baud_rate(true);

    uint16_t ticks = timer2_mode0_baudrate_to_ticks(uart_baudrate);

    timer2_mode0_start(ticks);

    return ticks;
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

