#ifndef STC15_UART19BITSHAREDH
#define STC15_UART19BITSHAREDH

#include <stdint.h>

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
    TB8 = (uint8_t)(nineth & 0x01);                         \
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
 * @param byte_ptr uint8_t* the 8-bit data value to be received (0-255).
 * @param nineth_ptr uint8_t* the 9th bit of the received data. 1 or 0.
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for receveive.
 * 
 * @warning Should not be called from interrupt service routines
 * 
 * @ingroup uart1_9bit_shared 
 */
#define uart1_receive_9bit(byte_ptr, nineth_ptr)            \
do {                                                        \
    while(!RI);                                             \
    *byte_ptr = SBUF;                                       \
    *nineth_ptr = (uint8_t)(RB8 & 0x01);                    \
    RI=0;                                                   \
while (0)

typedef enum {
    SPACE,
    MARK,
    ODD,
    EVEN
} uart1_parity_t;

void uart1_send_byte_with_parity(uint8_t byte, uart1_parity_t p);

void uart1_receive_byte_with_parity(uint8_t *byte, uart1_parity_t p);

#endif