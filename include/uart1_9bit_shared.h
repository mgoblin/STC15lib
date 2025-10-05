#ifndef STC15_UART19BITSHAREDH
#define STC15_UART19BITSHAREDH

#include <stdint.h>

#include <sys.h>
#include <uart1_shared.h>

#define uart1_send_9bit(byte, nineth)                       \
do {                                                        \
    TB8 = (uint8_t)(nineth & 0x01);                         \
    uart1_send_byte(byte);                                  \
} while (0)

#define uart1_receive_9bit(byte_ptr, nineth_ptr)            \
do {                                                        \
    while(!RI);                                             \
    *byte_ptr = SBUF;                                       \
    *nineth_ptr = (uint8_t)(RB8 & 0x01);                    \
    RI=0;                                                   \
while (0)    

#endif