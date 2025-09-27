#include <uart1_mode0.h>

void uart1_mode0_init()
{
    // Configure UART1 in Mode 0
    SCON = 0x50; // 8-bit data, no parity, 1 stop bit
}


void uart1_mode0_send_byte(uint8_t byte)
{
    if(TI==0)
    {
        SBUF = byte;
    }
}

void uart1_mode0_receive_byte(uint8_t *byte)
{
    if(RI==1)
    {
        *byte = SBUF;
        RI = 0;
    }
}