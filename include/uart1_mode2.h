#ifndef STC15_UART1MODE2H
#define STC15_UART1MODE2H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <interrupt.h>
#include <uart1_9bit_shared.h>

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
 * @see uart1_send_9bit()
 * @see uart1_receive_9bit()
 * @see is_uart1_send_byte_complete()
 * @see is_uart1_receive_byte_complete()
 
 * 
 * @author Michael Golovanov
 */
/**
 * @brief UART1 baud rate enumeration
 * 
 * @ingroup uart1_mode2
 */
typedef enum {
    baudrate_172800 = 172800U,
    baudrate_345600 = 345600U
} uart1_mode2_baudrate_t;

/** @name init
 *  UART1 initialization functions
 */
///@{

/**
 * @brief Initializes UART1 in Mode 0.
 * 
 * Must be called before any UART communication is initiated.
 * 
 * @param pins uart1_pins_t The desired UART1 pins.
 * @param baudRate uart1_mode2_baudrate_t The desired UART1 baud rate.
 * 
 * @attention Baud rate is biased by frequency divider.
 * 
 * @ingroup uart1_mode2
*/
#define uart1_mode2_init(pins, baudRate)                                        \
do {                                                                            \
    enable_mcu_interrupts();                                                    \
    enable_uart1_interrupt();                                                   \
                                                                                \
    /* PCON.7 always set to 1. Is it error? */                                  \
    baudRate == baudrate_345600 ? bit_set(PCON, SBIT7) : bit_clr(PCON, SBIT7);  \
                                                                                \
    /* SM1 = 1, SM0 = 0 to select UART1 mode2 */                                \
    SCON = 0x90;                                                                \
                                                                                \
    /* Set AUXR1 bits 6, 7 to select RxD/TxD pins */                            \
    AUXR1 &= 0x3F;                                                              \
    AUXR1 |= pins;                                                              \
} while (0)

///@}
#endif
