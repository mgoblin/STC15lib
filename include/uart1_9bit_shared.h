#ifndef STC15_UART19BITSHAREDH
#define STC15_UART19BITSHAREDH

#include <stdint.h>

#include <sys.h>
#include <uart1_shared.h>

void uart1_send_9bit(uint8_t byte, uint8_t nineth);

void uart1_receive_9bit(uint8_t *byte_ptr, uint8_t *nineth_ptr);

#endif