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
  * @brief UART1 parity type
  * 
  * @ingroup uart1_9bit_shared
  */
typedef enum {
    PARITY_SPACE,
    PARITY_MARK,
    PARITY_ODD,
    PARITY_EVEN
} uart1_parity_t;

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
 * @brief Send byte over UART1 in mode 2, 3 with parity bit
 * 
 * @param byte uint8_t byte to be sent
 * @param parity uart1_parity_t parity type
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_send_byte(byte, parity)           \
do {                                            \
    ACC = byte;                                 \
    if (parity == PARITY_EVEN)                  \
    {                                           \
        uart1_send_9bit(byte, P);               \
    }                                           \
    else if (parity == PARITY_ODD)              \
    {                                           \
        uart1_send_9bit(byte, ~P);              \
    }                                           \
    else if (parity == PARITY_SPACE)            \
    {                                           \
        uart1_send_9bit(byte, 0);               \
    }                                           \
    else if (parity == PARITY_MARK)             \
    {                                           \
        uart1_send_9bit(byte, 1);               \
    }                                           \
} while (0)    

bool uart1_receive_byte(uint8_t *byte, uart1_parity_t parity);

#endif