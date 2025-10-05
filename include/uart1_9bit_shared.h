#ifndef STC15_UART19BITSHAREDH
#define STC15_UART19BITSHAREDH

#include <stdint.h>

#include <sys.h>

void uart1_send_9bit(uint8_t byte, __bit nineth);

#endif