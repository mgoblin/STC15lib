#ifndef STC15_UART19BITSHAREDH
#define STC15_UART19BITSHAREDH

#include <stdint.h>
#include <stdbool.h>

#include <sys.h>

/**
 * @file uart1_9bit_shared.h
 * 
 * @defgroup uart1_9bit_shared UART1 9bit send/receive functions
 * 
 * @details Functions for sending and receiving 9-bit data in 
 * UART1 mode 2 and 3.
 * 
 * This header file included in UART1 mode 2, 3 headers and 
 * do not need to be included explicitly.
 * 
 * @author Michael Golovanov
 */

 /**
  * @brief Send 9-bit data over UART1 in mode 2, 3
  * 
  * @details
  * The function blocks until the byte is fully transmitted.
  * 
  * @note Requires UART1 to be previously initialized and started.
  * @note Uses polling (blocking) method for transmission.
  * 
  * @param byte uint8_t byte to be sent
  * @param nineth uint8_t 9th bit of the byte to be sent. Should be 0 or 1.
  * 
  * @warning Should not be called from interrupt service routines
  * 
  * @ingroup uart1_9bit_shared 
  */
#define uart1_send_9bit(byte, nineth)                       \
do {                                                        \
    TB8 = nineth;                                           \
    SBUF = byte;                                            \
                                                            \
    while (!TI);                                            \
    TI = 0;                                                 \
} while (0)

/**
 * @brief Receive 9-bit data over UART1 in mode 2, 3
 * 
 * @details
 * The function blocks until the 9bits is fully received.
 * 
 * @param byte uint8_t the 8-bit data value to be received (0-255).
 * @param nineth uint8_t the 9th bit of the received data. 1 or 0.
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for receveive.
 * 
 * @warning Should not be called from interrupt service routines
 * 
 * @ingroup uart1_9bit_shared 
 */
#define uart1_receive_9bit(byte, nineth)                    \
do {                                                        \
    RI=0;                                                   \
    while(!RI);                                             \
    byte = SBUF;                                            \
    nineth = RB8;                                           \
while (0)

/**
 * @brief Send byte over UART1 in mode 2, 3 
 * with even parity bit
 * 
 * @param byte uint8_t byte to be sent
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_send_byte_even_parity(byte)       \
do {                                            \
    ACC = byte;                                 \
    uart1_send_9bit(byte, P);                   \
} while (0)    

/**
 * @brief Send byte over UART1 in mode 2, 3 
 * with odd parity bit
 * 
 * @param byte uint8_t byte to be sent
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_send_byte_odd_parity(byte)        \
do {                                            \
    ACC = byte;                                 \
    uart1_send_9bit(byte, !P);                  \
} while (0)

/**
 * @brief Send byte over UART1 in mode 2, 3 
 * with space parity bit
 * 
 * @param byte uint8_t byte to be sent
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_send_byte_space_parity(byte)      \
do {                                            \
    uart1_send_9bit(byte, 0);                   \
} while (0)    

/**
 * @brief Send byte over UART1 in mode 2, 3 
 * with mark parity bit
 * 
 * @param byte uint8_t byte to be sent
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_send_byte_mark_parity(byte)       \
do {                                            \
    uart1_send_9bit(byte, 1);                   \
} while (0)    

/**
 * @brief Receive byte over UART1 in mode 2, 3 with even parity bit
 * 
 * @param byte uint8_t the 8-bit data value to be received (0-255).
 * 
 * @attention This function is blocking until the byte is fully received with 
 * valid parity bit. Receive byte with non-valid parity bit will not 
 * unblock the function.
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_receive_byte_even_parity(byte)    \
do {                                            \
    bool is_parity_valid = false;               \
    while (!is_parity_valid)                    \
    {                                           \
        RI = 0;                                 \
        while (!RI);                            \
                                                \
        byte = SBUF;                            \
                                                \
        ACC = byte;                             \
                                                \
        is_parity_valid = P != RB8;             \
    }                                           \
} while (0)        

#endif