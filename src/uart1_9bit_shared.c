#include <uart1_9bit_shared.h>

void uart1_send_byte(uint8_t byte, uart1_parity_t parity)
{
    ACC = byte;
    const uint8_t parity_bit = P;
    if(parity == PARITY_EVEN)
    {
        uart1_send_9bit(byte, parity_bit);
    } else if(parity == PARITY_ODD)
    {
        uart1_send_9bit(byte, ~parity_bit);
    } else if(parity == PARITY_SPACE)
    {
        uart1_send_9bit(byte, 0);
    } else if (parity == PARITY_MARK)
    {
        uart1_send_9bit(byte, 1);
    }
}

void uart1_receive_byte(uint8_t *byte, bool *is_parity_valid, uart1_parity_t parity)
{
    // Get received 8 bits from SBUF and parity bit from RB8
    // Check parity. 
    // If partity is valid, store received byte in *byte and store true in *is_parity_valid
    // If parity is not valid, store false in *is_parity_valid and do not store received byte
    // in *byte
}