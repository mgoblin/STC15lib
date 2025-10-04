#ifndef STC15_UART1MODE2H
#define STC15_UART1MODE2H

#include <stdint.h>
#include <stdbool.h>

#include <sys.h>
#include <bits.h>
#include <interrupt.h>
#include <uart1_shared.h>

typedef enum {
    baudrate_172800 = 172800U,
    baudrate_345600 = 345600U
} uart1_mode2_baudrate_t;

void uart1_mode2_init(uart1_pins_t pins, uart1_mode2_baudrate_t baudRate);

#endif
