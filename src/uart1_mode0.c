#include <uart1_mode0.h>

void uart1_mode0_init(BaudRate_t baudRate)
{
    // Configure UART1 in Mode 0
    PCON &= 0x3F;
    SCON = 0;

    baudRate == UART_BaudRate_921600 ? 
        bit_clr(AUXR, CBIT5) : bit_set(AUXR, SBIT5);
}


void uart1_mode0_send_byte(uint8_t byte)
{
    SBUF = byte;
    while (!TI);
    TI = 0;
}