#include <uart1_mode0.h>

void uart1_mode0_init()
{
    // Configure UART1 in Mode 0
    PCON &= 0x3F;
    SCON = 0;
}


void uart1_mode0_send_byte(uint8_t byte)
{
    SBUF = byte;
    while (!TI);
    TI = 0;
}