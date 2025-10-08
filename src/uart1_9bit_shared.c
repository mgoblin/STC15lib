#include <uart1_9bit_shared.h>

void uart1_receive_byte(uint8_t *byte, bool *is_parity_valid, uart1_parity_t parity)
{
    // Get received 8 bits from SBUF and parity bit from RB8
    // Check parity. 
    // If partity is valid, store received byte in *byte and store true in *is_parity_valid
    // If parity is not valid, store false in *is_parity_valid and do not store received byte
    // in *byte
}