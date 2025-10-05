#ifndef STC15_UART1MODE3_T212H
#define STC15_UART1MODE3_T212H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <frequency.h>
#include <interrupt.h>
#include <uart1_shared.h>

/**
 * @file uart1_mode3_timer2_12T.h
 * 
 * @defgroup uart1_mode3_timer2_12T  UART1 Mode 3 with Timer2 12T
 * 
 * @details
 * Functions and data structures for UART1 communication in Mode 3 
 * with Timer2 12T as baudrate generator. 
 * Dont use Timer2 for other purposes.
 * 
 * This module implements UART1 point-to-point communication.
 * Relay and broadcast features are not supported by this module.
 *
 * UART1 Mode 3 provides 9-bit asynchronous communication with variable baud rate.
 * Sent data is transmitted to the TxD pin, and received data is read from the RxD pin.
 * The frame data includes one start bit, 9 data bits, and one stop bit.
 * 9-N-1
 * 
 * UART1 baudrate is determined by the T2 overflow rate.
 * T2 overflow rate is configured by setting T2H and T2L registers.
 * 
 * THTL = 65536 - (Sysclk/12)/(4 * baudrate).
 * Sysclk = master clock frequency / frequency divder.
 * 
 * THTL value is precalulated for standard baudrates with none freq divider.
 * 
 * In UART1 Mode 1, three sets of RxD/TxD pins can be used: 
 * RxD on P3.0/TxD on P3.1, RxD on P3.6/TxD on P3.7 and 
 * RxD on P1.6/TxD on P1.7.
 * 
 * Typical usage:
 * ```c
 * uart1_mode3_timer2_12T_init(RxD_P30_TxD_P31);
 * uart1_mode3_timer2_12T_start(baudrate_9600);
 * 
 * for (;;)
 * {
 *  // Send or receive data
 * }
 * 
 * ``` 
 * 
 * @see uart1_send_byte()
 * @see uart1_receive_byte()
 * @see is_uart1_send_byte_complete()
 * @see is_uart1_receive_byte_complete()
 * 
 * @author Michael Golovanov
*/

/**
 * @brief UART1 Mode3 precalculated baudrates
 * 
 * @ingroup uart1_mode3_timer2_12T
 */
typedef enum 
{
    /** @brief 1200 baudrate */
    baudrate_1200 = 0xFF3F,
    /** @brief 2400 baudrate */
    baudrate_2400 = 0xFF9F,
    /** @brief 4800 baudrate */
    baudrate_4800 = 0xFFCF,
    /** @brief 9600 baudrate */
    baudrate_9600 = 0xFFE7,
} uart1_mode3_timer2_12t_baudrate_t;

#define uart1_mode3_timer2_12T_init(pins)                       \
do {                                                            \
    enable_mcu_interrupts();                                    \
    enable_uart1_interrupt();                                   \
    disable_timer2_interrupt();                                 \
                                                                \
    PCON &= 0x3F;                                               \
    SCON = 0xD0;                                                \
                                                                \
    /* The clock source of Timer 2 is SYSclk/12. AUXR.T2x12 = 0 */ \
    /* AUXR.UART_M0x6 = 0 */                                    \
    /* Timer2 is not started. AUXR.T2R = 0 */                   \
    /* Timer2 are used as timer. AUXR.T2_C/T = 0 */             \
    AUXR &= 0xC2;                                               \
                                                                \
    /* Select Timer2 as UART1 baud rate generator. AUXR.S1ST2 = 1; */ \
    bit_set(AUXR, SBIT0);                                       \
                                                                \
    /* Point-to-point mode */                                   \
    bit_clr(CLK_DIV, CBIT4);                                    \
                                                                \
    /* Set AUXR1 bits 6, 7 to select RxD/TxD pins */            \
    AUXR1 &= 0x3F;                                              \
    AUXR1 |= pins;                                              \
} while (0)

#define uart1_mode3_timer2_12T_start(baudrate)                  \
do {                                                            \
    /* Set TH TL values */                                      \
    T2L = baudrate & 0xFF;                                      \
    T2H = baudrate >> 8;                                        \
                                                                \
    /* Start Timer2 */                                          \
    bit_set(AUXR, SBIT4);                                       \
} while (0)

#define uart1_mode3_timer2_12T_ticks(baudrate) (65536 - ((((MAIN_Fosc / 12) / baudrate) >> 2) >> get_frequency_divider_scale()))

#define uart1_mode3_timer2_12T_start_ext(baudrate)              \
do {                                                            \
    const uint16_t ticks = uart1_mode1_timer2_12T_ticks(baudrate);\
                                                                \
    /* Set TH TL values */                                      \
    T2L = ticks & 0xFF;                                         \
    T2H = ticks >> 8;                                           \
                                                                \
    /* Start Timer2 */                                          \
    bit_set(AUXR, SBIT4);                                       \
} while (0)


#define uart1_mode3_timer2_12T_stop (bit_clr(AUXR, CBIT4))

#define is_uart1_mode3_timer2_12T_started() (test_if_bit_set(AUXR, SBIT4))

#endif