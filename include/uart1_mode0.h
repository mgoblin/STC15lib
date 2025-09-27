#ifndef STC15_UART1MODE0H
#define STC15_UART1MODE0H

#include <stdint.h>

#include <sys.h>

/**
 * @file uart1_mode0.h
 * @defgroup uart1_mode0 UART1 Mode 0
 * @details Functions and data structures for UART1 communication in Mode 0.
 * 
 * Mode 0 provides synchronous communication with fixed baud rate.
 * 
 * @author Michael Golovanov
 * 
*/

/** @name init
 *  UART1 initializaion functions
 */
///@{

/**
 * @brief Initializes UART1 in Mode 0.
 * 
 * Must be called before any UART communication is initiated.
 * 
 * @note Assumes system clock is already configured.
 * @note Modifies UART1 control and status registers.
 * 
 * @ingroup uart1_mode0
 */
void uart1_mode0_init();
///@}

/** @name send and receive
 *  UART1 send and receive byte functions
 */
///@{

/**
 * @brief Sends a single byte over UART1 in Mode 0.
 * 
 * Transmits the specified 8-bit data byte through UART1 configured in Mode 0.
 * The function blocks until the byte is fully transmitted.
 * 
 * @param byte The 8-bit data value to be sent (0-255).
 * 
 * @note Requires UART1 to be previously initialized with uart_mode0_init().
 * @note Uses polling (blocking) method for transmission.
 * @note Assumes UART1 is configured with 8 data bits, no parity, 1 stop bit.
 * 
 * @ingroup uart1_mode0
 */
void uart1_mode0_send_byte(uint8_t byte);

/**
 * @brief Receives a single byte from UART1.
 * 
 * Waits until a byte is received via UART1 and stores it in the provided memory location.
 * 
 * @param[out] byte Pointer to a uint8_t where the received data will be stored.
 * 
 * @note This function blocks until a byte is received.
 * @note Requires UART1 to be initialized with uart_mode0_init() prior to use.
 * @note Assumes UART1 is configured with 8 data bits, no parity, 1 stop bit.
 * 
 * @ingroup uart1_mode0
 */
void uart1_mode0_receive_byte(uint8_t *byte);

///@}

#endif