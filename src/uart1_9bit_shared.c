#include <uart1_9bit_shared.h>

void uart1_send_9bit(uint8_t byte, __bit nineth)
{
   TB8 = nineth;
   uart1_send_byte(byte);

}