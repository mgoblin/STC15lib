#include <uart1_9bit_shared.h>

void uart1_send_9bit(uint8_t byte, uint8_t nineth)
{
   TB8 = (uint8_t)(nineth & 0x01);
   uart1_send_byte(byte);
}

void uart1_receive_9bit(uint8_t *byte_ptr, uint8_t *nineth_ptr)
{
   while(!RI);
   *byte_ptr = SBUF;
   *nineth_ptr = (uint8_t)(RB8 & 0x01);
   RI=0;
}