#ifndef STC15_UART19BITSHAREDH
#define STC15_UART19BITSHAREDH

#include <stdint.h>
#include <stdbool.h>

#include <sys.h>

/**
 * @file uart1_9bit_shared.h
 * 
 * @defgroup uart1_9bit_shared UART1 9bit, 8-bit with parity, 8-bit with two stop bits send/receive functions
 * 
 * @details This module contains functions:
 * * Sending and receiving 9-bit data in 
 * UART1 mode 2 and 3.
 * * Sending and receiving 8-bit data with parity bit
 * in UART1 mode 2 and 3.
 * * Sending and receiving 8-bit data with 2 stop bits
 * in UART1 mode 2 and 3.
 * 
 * This header file included in UART1 mode 2, 3 headers and 
 * do not need to be included explicitly.
 * 
 * @author Michael Golovanov
 */

 /** @name 9-bit
 *  9-bit receive and send functions
 */
///@{

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
  * @param ninth uint8_t 9th bit of the byte to be sent. Should be 0 or 1.
  * 
  * @warning Should not be called from interrupt service routines
  * 
  * @ingroup uart1_9bit_shared 
  */
#define uart1_send_9bit(byte, ninth)                        \
do {                                                        \
    /* TB8 contains 9-th bit value */                       \
    TB8 = ninth;                                            \
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
 * @param ninth uint8_t the 9th bit of the received data. 1 or 0.
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for receveive.
 * 
 * @warning Should not be called from interrupt service routines
 * 
 * @ingroup uart1_9bit_shared 
 */
#define uart1_receive_9bit(byte, ninth)                     \
do {                                                        \
    RI=0;                                                   \
    while(!RI);                                             \
    /* After RI flag set to 1 */                            \
    /* SBUF contains first 8-bit data  */                   \
    /* and RB8 contains 9th bit */                          \
    byte = SBUF;                                            \
    ninth = RB8;                                            \
} while (0)

///@}

/** @name 8-bit with parity bit
 *  8-bit receive and send with parity bit functions 
 */
///@{

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
    /* P is even parity bit for ACC value */    \
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
#define uart1_send_byte_odd_parity(byte)         \
do {                                             \
    /* P is even parity bit for ACC value */     \
    ACC = byte;                                  \
    /* For the odd parity P should be inverted*/ \
    uart1_send_9bit(byte, !P);                   \
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
    /** Parity bit is always 0 */               \
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
    /* Parity bit is always 1 */                \
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
    /* Try to receive byte */                   \
    /* util parity bit is to be valid */        \
    bool is_parity_valid = false;               \
    while (!is_parity_valid)                    \
    {                                           \
        /* Receive 8-bit to SBUF */             \
        /* and parity bit to RB8 */             \
        RI = 0;                                 \
        while (!RI);                            \
                                                \
        byte = SBUF;                            \
                                                \
        /* Load received 8-bit to ACC for */    \
        /* even parity calculation */           \
        ACC = byte;                             \
                                                \
        /* Validate received and calculated */  \
        /* parity bits */                       \
        is_parity_valid = P == RB8;             \
    }                                           \
} while (0)        

/**
 * @brief Receive byte over UART1 in mode 2, 3 with odd parity bit
 * 
 * @param byte uint8_t the 8-bit data value to be received (0-255).
 * 
 * @attention This function is blocking until the byte is fully received with 
 * valid parity bit. Receive byte with non-valid parity bit will not 
 * unblock the function.
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_receive_byte_odd_parity(byte)     \
do {                                            \
    /* Try to receive byte */                   \
    /* util parity bit is to be valid */        \
    bool is_parity_valid = false;               \
    while (!is_parity_valid)                    \
    {                                           \
        /* Receive 8-bit to SBUF */             \
        /* and parity bit to RB8 */             \
        RI = 0;                                 \
        while (!RI);                            \
                                                \
        byte = SBUF;                            \
                                                \
        /* Load received 8-bit to ACC for */    \
        /* even parity calculation */           \
        ACC = byte;                             \
                                                \
        /* For odd parity even parity P */      \
        /* should be inverted */                \
        is_parity_valid = P != RB8;             \
    }                                           \
} while (0)       

/**
 * @brief Receive byte over UART1 in mode 2, 3 with mark parity bit
 * 
 * @param byte uint8_t the 8-bit data value to be received (0-255).
 * 
 * @attention This function is blocking until the byte is fully received with 
 * valid parity bit. Receive byte with non-valid parity bit will not 
 * unblock the function.
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_receive_byte_mark_parity(byte)    \
do {                                            \
    /* Try to receive byte */                   \
    /* util parity bit is to be valid */        \
    bool is_parity_valid = false;               \
    while (!is_parity_valid)                    \
    {                                           \
        RI = 0;                                 \
        while (!RI);                            \
                                                \
        byte = SBUF;                            \
                                                \
        /* RB8 contains parity bit */           \
        is_parity_valid = RB8 == 1;             \
    }                                           \
} while (0)       

/**
 * @brief Receive byte over UART1 in mode 2, 3 with space parity bit
 * 
 * @param byte uint8_t the 8-bit data value to be received (0-255).
 * 
 * @attention This function is blocking until the byte is fully received with 
 * valid parity bit. Receive byte with non-valid parity bit will not 
 * unblock the function.
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_receive_byte_space_parity(byte)   \
do {                                            \
    /* Try to receive byte */                   \
    /* util parity bit is to be valid */        \
    bool is_parity_valid = false;               \
    while (!is_parity_valid)                    \
    {                                           \
        RI = 0;                                 \
        while (!RI);                            \
                                                \
        byte = SBUF;                            \
                                                \
        /* RB8 contains parity bit */           \
        is_parity_valid = RB8 == 0;             \
    }                                           \
} while (0)
///@}

/** @name 8-bit-2-stop-bit functions
 *  8-bit with two stop bits receive and send functions
 */
///@{

/**
 * @brief Send byte over UART1 in mode 2, 3 with 2 stop bits
 * 
 * @param byte uint8_t the 8-bit data value to be sent (0-255).
 * 
 * @attention This function is blocking until the byte is fully sent.
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_send_byte_2stop_bits(byte)        \
do {                                            \
    uart1_send_9bit(byte, 1);                   \
} while (0)    

/**
 * @brief Receive byte over UART1 in mode 2, 3 with 2 stop bits
 * 
 * @param byte uint8_t the 8-bit data value to be received (0-255).
 * 
 * @attention This function is blocking until the byte is fully received 
 * with valid stop bits.
 * 
 * @ingroup uart1_9bit_shared
 */
#define uart1_receive_byte_2stop_bits(byte)         \
do {                                                \
    uart1_receive_byte_mark_parity(byte);           \
} while (0)

///@}

#endif