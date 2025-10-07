#ifndef STC15_UART18BITSHAREDH
#define STC15_UART18BITSHAREDH

#include <stdint.h>

#include <sys.h>

/**
 * @file uart1_8bit_shared.h
 * 
 * @defgroup uart1_8bit_shared UART1 8-bit send/receive functions
 * 
 * @details UART1 routines used in all UART1 modes.
 * 
 * This header file included in UART1 mode headers and 
 * do not need to be included explicitly.
 * 
 * @author Michael Golovanov
 */

/**
 * @brief Sends a single byte over UART1.
 * 
 * @details 
 * Transmits the specified byte through UART1.
 * The function blocks until the byte is fully transmitted.
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for transmission.
 *
 * 
 * @param byte uint8_t byte to be sent
 * 
 * @warning Should not be called from interrupt service routines
 * 
 * @ingroup uart1_8bit_shared
 */
#define uart1_send_byte(byte)                   \
do                                              \
{                                               \
    SBUF = byte;                                \
    while (!TI);                                \
    TI = 0;                                     \
} while (0)

/**
 * @brief Checks if UART1 send byte operation is complete.
 * 
 * @attention Use this function only in UART 1interrupt service routine.
 * 
 * @ingroup uart1_8bit_shared
 */
#define is_uart1_send_byte_complete() (TI) 

/**
 * @brief Receives a single byte over UART1.
 * 
 * @details 
 * The function blocks until the byte is fully received.
 * 
 * @param byte_ptr uint8_t* the 8-bit data value to be received (0-255).
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for receveive.
 *
 * @warning Should not be called from interrupt service routines
 * 
 * @ingroup uart1_8bit_shared
 */
#define uart1_receive_byte(byte_ptr)            \
do {                                            \
	while(!RI);                                 \
    *byte_ptr = SBUF;                           \
	RI=0;                                       \
} while (0)

/**
 * @brief Checks if UART1 receive byte operation is complete.
 * 
 * @attention Use this function only in UART 1interrupt service routine.
 * 
 * @ingroup uart1_8bit_shared
 */
#define is_uart1_receive_byte_complete() (RI)

#endif
