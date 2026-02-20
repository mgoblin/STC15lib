#ifndef STC15_UART1MODE1_T212H
#define STC15_UART1MODE1_T212H

/**
 * @file uart1_mode1_timer2_1T.h
 * @defgroup uart1_mode1_timer2_1T  UART1 Mode 1 with Timer2 1T
 * 
 * @details 
 * Functions and data structures for UART1 communication in Mode 1 
 * with Timer2 1T as baudrate generator. 
 * Dont use Timer2 for other purposes.
 * 
 * This module implements UART1 point-to-point communication.
 * Relay and broadcast features are not supported by this module.
 * 
 * UART1 Mode 1 provides 8-bit asynchronous communication with variable baud rate.
 * Sent data is transmitted to the TxD pin, and received data is read from the RxD pin.
 * The frame data includes one start bit, 8 data bits, and one stop bit.
 * 8-N-1
 * 
 * UART1 baudrate is determined by the T2 overflow rate.
 * T2 overflow rate is configured by setting T2H and T2L registers.
 * 
 * THTL = 65536 - Sysclk/(4 * baudrate).
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
 * uart1_mode1_timer2_1T_init(RxD_P30_TxD_P31);
 * uart1_mode1_timer2_1T_start(baudrate_9600);
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

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <frequency.h>
#include <interrupt.h>
#include <uart1_shared.h>
#include <uart1_8bit_shared.h>

/**
 * @brief UART1 precalculated baudrates
 * 
 * @ingroup uart1_mode1_timer2_1T
 */
typedef enum : unsigned int
{
    /** @brief 1200 baudrate */
    baudrate_1200 = 0xF6FF,
    /** @brief 2400 baudrate */
    baudrate_2400 = 0xFB80,
    /** @brief 4800 baudrate */
    baudrate_4800 = 0xFDC0,
    /** @brief 9600 baudrate */
    baudrate_9600 = 0xFEE0,
    /** @brief 19200 baudrate */
    baudrate_19200 = 0xFF70,
    /** @brief 38400 baudrate */
    baudrate_38400 = 0xFFB8,
    /** @brief 57600 baudrate */
    baudrate_57600 = 0xFFD0,
    /** @brief 115200 baudrate */
    baudrate_115200 = 0xFFE8
} uart1_mode1_timer2_1t_baudrate_t;


/**
 * @brief Initialize UART1 in Mode 1 with Timer2 1T configuration
 * 
 * @details
 * The clock source of Timer2 is SYSclk. AUXR.T2x12 = 1.
 * AUXR.UART_M0x6 = 0.
 * Timer2 are used as timer. AUXR.T2_C/T = 0.
 * Timer2 is not started. AUXR.T2R = 0.
 * 
 * @see uart1_pins_t
 * 
 * @param pins Pin configuration from uart1_pins_t enum
 * 
 * @note Must be called before starting UART communication
 * 
 * @ingroup uart1_mode1_timer2_1T
 */
#define uart1_mode1_timer2_1T_init(pins)   \
do {                                        \
                                            \
    enable_mcu_interrupts();                \
    enable_uart1_interrupt();               \
    disable_timer2_interrupt();             \
                                            \
    PCON &= 0x3F;                           \
    SCON = 0x50;                            \
                                            \
    /* The clock source of Timer 2 is SYSclk/12. AUXR.T2x12 = 0 */  \
    /* AUXR.UART_M0x6 = 0 */                                        \
    /* Timer2 is not started. AUXR.T2R = 0 */                       \
    /* Timer2 are used as timer. AUXR.T2_C/T = 0 */                 \
    AUXR &= 0xC2;                           \
                                            \
    /* Select Timer2 as UART1 baud rate generator. AUXR.S1ST2 = 1; */ \
    bit_set(AUXR, SBIT0);                   \
    /* The clock source of Timer 2 is SYSclk. AUXR.T2x12 = 1 */       \
    bit_set(AUXR, SBIT2);                   \
                                            \
    /* Point-to-point mode */               \
    bit_clr(CLK_DIV, CBIT4);                \
                                            \
    /* Set AUXR1 bits 6, 7 to select RxD/TxD pins */                 \
    AUXR1 &= 0x3F;                          \
    AUXR1 |= pins;                          \
} while(0)

/**
 * @brief Start UART1 communication with standart baudrate value
 * 
 * @ingroup uart1_mode1_timer2_1T
 * 
 * @param baudrate const uart1_mode1_timer2_1t_baudrate_t Baudrate selection from uart1_mode1_timer2_1t_baudrate_t enum
 * 
 * @note Before calling this function, uart1_mode1_timer2_1T_init() must be called.
 * @note Enum contains standard baudrates with precalculated THTL values for 1T mode
 * 
 * @warning UART1 mode1 in this routine is biased by frequency divider.
 */
#define uart1_mode1_timer2_1T_start(baudrate)           \
do {                                                    \
    /* Set TH TL values */                              \
    T2L = baudrate & 0xFF;                              \
    T2H = baudrate >> 8;                                \
                                                        \
    /* Start Timer2 */                                  \
    bit_set(AUXR, SBIT4);                               \
} while(0)

/**
 * @brief Get UART1 ticks for given baudrate and frequency divider scale
 * 
 * @details Ticks used as input parameter for uart1_mode1_timer2_1T_start_ext()
 * 
 * @param baudrate uint32_t baudrate
 * 
 * @return uint16_t baudrate ticks 
 * 
 * @attention This function is not overflow safe. 
 * The value of (((MAIN_Fosc / baudrate) >> 2) >> get_frequency_divider_scale())
 * should be less than 65535 (uint16_t).
 * 
 * @ingroup uart1_mode1_timer2_1T
 */
#define uart1_mode1_timer2_1T_ticks(baudrate) (65536 - (((MAIN_Fosc / baudrate) >> 2) >> get_frequency_divider_scale()))

/**
 * @brief Start UART1 communication with baudrate value
 * 
 * @ingroup uart1_mode1_timer2_1T
 * 
 * @param baudrate const uint32_t Baudrate value. Value may be non standard (not in 1200, 9600 etc).
 * 
 * @note Before calling this function, uart1_mode1_timer2_1T_init() must be called.
 * 
 * @attention This function is not baudrate overflow safe.
 */
#define uart1_mode1_timer2_1T_start_ext(baudrate)              \
do {                                                            \
    const uint16_t ticks = uart1_mode1_timer2_1T_ticks(baudrate);\
                                                                \
    /* Set TH TL values */                                      \
    T2L = ticks & 0xFF;                                         \
    T2H = ticks >> 8;                                           \
                                                                \
    /* Start Timer2 */                                          \
    bit_set(AUXR, SBIT4);                                       \
} while (0)


/**
 * @brief Stop UART1 communication and disable Timer2
 * 
 * @ingroup uart1_mode1_timer2_1T
 * 
 * @warning Calling this function will terminate any ongoing communication
 */
#define uart1_mode1_timer2_1T_stop (bit_clr(AUXR, CBIT4))

/**
 * @brief Is UART1 started?
 * @return bool returns true if UART1 started otherwise false.
 * 
 * @ingroup uart1_mode1_timer2_1T
 */
#define is_uart1_mode1_timer2_1T_started() (test_if_bit_set(AUXR, SBIT4))


#endif