#ifndef STC15_UART1MODE0H
#define STC15_UART1MODE0H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <interrupt.h>
#include <uart1_shared.h>

/**
 * @file uart1_mode0.h
 * @defgroup uart1_mode0 UART1 Mode 0
 * 
 * @details Functions and data structures for UART1 communication in Mode 0.
 * 
 * Mode 0 provides synchronous communication with fixed baud rate.
 * 
 * Serial data enters and exits through RxD. TxD outputs the shift clock. 
 * Eight data bits are transmitted/received with the least-significant (LSB) first. 
 * The baud rate is fixed at 1/12 (or 1/2) the System clock cycle.
 * 
 * This module routines does not support UART1 interrupts.
 * 
 * @author Michael Golovanov
 * 
*/

/**
 * @brief UART1 baud rate enumeration
 * 
 * @ingroup uart1_mode0
 */
typedef enum {
    baudrate_921600 = 921600U,
    baudrate_5529600 = 5529600U
} uart1_mode0_baudrate_t;

/** @name init
 *  UART1 initializaion functions
 */
///@{

/**
 * @brief Initializes UART1 in Mode 0.
 * 
 * Must be called before any UART communication is initiated.
 * 
 * @param baudRate BaudRate_t The desired baud rate.
 * 
 * @note Assumes system clock is already configured.
 * @note Modifies UART1 control and status registers. Disables UART1 interrupt.
 * 
 * @ingroup uart1_mode0
 */
#define uart1_mode0_init(baudRate)                  \
do                                                  \
{                                                   \
    PCON &= 0x3F;                                   \
    SCON = 0;                                       \
    baudRate == baudrate_921600 ?                   \
        bit_clr(AUXR, CBIT5) : bit_set(AUXR, SBIT5);\
    disable_uart1_interrupt();                      \
} while (0)
///@}

/** @name send and receive
 *  UART1 send and receive byte functions
 */
///@{

/**
 * @brief Sends a single byte over UART1 in Mode 0.
 * 
 * @details 
 * Alias for @ref uart1_send_byte().
 * 
 * RxD and TxD pins state diagram are pictured at 
 * @image html UART1_mode0.png
 * 
 * @param byte uintT8_t the 8-bit data value to be sent (0-255).
 * 
 * @note Requires UART1 to be previously initialized with uart_mode0_init().
 * @note Uses polling (blocking) method for transmission.
 *
 * 
 * @ingroup uart1_mode0
 */
#define uart1_mode0_send_byte(byte)             \
do                                              \
{                                               \
    uart1_send_byte(byte);                      \
} while (0)

/**
 * @brief Receives a single byte over UART1 in Mode 0.
 * 
 * @details 
 * Alias for @ref uart1_receive_byte().
 * 
 * @param byte_ptr byte* uintT8_t the 8-bit data value to be received (0-255).
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for receveive.
 *
 * 
 * @ingroup uart1_mode0
 */
#define uart1_mode0_receive_byte(byte_ptr)      \
do {                                            \
	uart1_receive_byte(byte_ptr);               \
} while (0)
///@}

#endif