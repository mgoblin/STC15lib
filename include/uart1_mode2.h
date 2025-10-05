#ifndef STC15_UART1MODE2H
#define STC15_UART1MODE2H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <interrupt.h>
#include <uart1_shared.h>

/**
 * @file uart1_mode2.h
 * @defgroup uart1_mode2 UART1 Mode2
 * 
 * @details Functions and data structures for UART1 communication in Mode 2.
 * 
 * Mode 2 provides asynchronous communication with fixed baud rate and 9-bit data.
 * 9-N-1.
 * 
 * The baud rate is fixed at 1/32 (or 1/64) the System clock cycle.
 * 
 * @attention Baud rate is biased by frequency divider
 * 
 * @see uart1_send_byte()
 * @see uart1_receive_byte()
 * @see is_uart1_send_byte_complete()
 * @see is_uart1_receive_byte_complete()
 
 * 
 * @author Michael Golovanov
 */

typedef enum {
    baudrate_172800 = 172800U,
    baudrate_345600 = 345600U
} uart1_mode2_baudrate_t;

void uart1_mode2_init(uart1_pins_t pins, uart1_mode2_baudrate_t baudRate);

#endif
