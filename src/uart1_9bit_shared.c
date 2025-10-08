#include <uart1_9bit_shared.h>

bool uart1_receive_byte(uint8_t *byte, uart1_parity_t parity)
{
    RI = 0;
    while (!RI);

    ACC = SBUF;
    const uint8_t parity_value = P;

    *byte = SBUF;

    return parity_value == RB8;

    // if (parity == PARITY_EVEN)
    // {
    //     return parity_value == RB8;
    // } else if (parity == PARITY_ODD)
    // {
    //     return parity_value != RB8;
    // } else if (parity == PARITY_SPACE) {
    //     return parity_value == 0;
    // } else if (parity == PARITY_MARK) 
    // {
    //     return parity_value == 1;
    // } else 
    // {
    //     return false;
    // }
}