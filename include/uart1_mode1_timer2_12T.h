#ifndef STC15_UART1MODE1H
#define STC15_UART1MODE1H

/**
 * @file uart1_mode1_timer2_12T.h
 * @defgroup uart1_mode1_timer2_12T  UART1 Mode 1 with Timer2 12T
 * 
 * @details 
 * Functions and data structures for UART1 communication in Mode 1 
 * with Timer2 12T as baudrate generator. 
 * Dont use Timer2 for other purposes.
 * 
 * This module implements UART1 point-to-point communication.
 * Relay and broadcast features are not supported by this module.
 * 
 * UART1 Mode 1 provides 8-bit asynchronous communication with variable baud rate.
 * Sent data is transmitted to the TxD pin, and received data is read from the RxD pin.
 * The frame data includes one start bit, 8 data bits, and one stop bit.
 * 
 * UART1 baudrate is determined by the T2 overflow rate.
 * T2 overflow rate is configured by setting T2H and T2L registers.
 * 
 * THTL = 65535 - (Sysclk/12)/(4 * baudrate).
 * Sysclk = master clock frequency / frequency divder.
 * 
 * THTL value is precalulated for standard baudrates.
 * 
 * In UART1 Mode 1, three sets of RxD/TxD pins can be used: 
 * RxD on P3.0/TxD on P3.1, RxD on P3.6/TxD on P3.7 and 
 * RxD on P1.6/TxD on P1.7.
 * 
 * Typical usage:
 * ```c
 * uart1_mode1_timer2_init(RxD_P30_TxD_P31);
 * uart1_mode1_timer2_start(baudrate_9600);
 * 
 * for (;;)
 * {
 *  // Send or receive data
 * }
 * 
 * ``` 
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <timer2_mode0.h>

/**
 * @brief UART1 RxD/TxD pins enum
 * 
 * @ingroup uart1_mode1_timer2_12T
 */
typedef enum 
{
    
    /** @brief RxD on P3.0 and TxD on P3.1 pins */
    RxD_P30_TxD_P31 = 0x00,
    /** @brief RxD on P3.6 and TxD on P3.7 pins */
    RxD_P36_TxD_P37 = 0x40,
    /** @brief RxD on P1.6 and TxD on P1.7 pins */
    RxD_P16_TxD_P17 = 0x80,

} uart1_pins_t;

/**
 * @brief UART1 precalculated baudrates
 * 
 * @ingroup uart1_mode1_timer2_12T
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
} uart1_mode1_timer2_12t_baudrate_t;

/**
 * @brief Initialize UART1 in Mode 1 with Timer2 12T configuration
 * 
 * @details
 * The clock source of Timer2 is SYSclk/12. AUXR.T2x12 = 0.
 * No double baud rate. AUXR.UART_M0x6 = 0.
 * Timer2 are used as timer. AUXR.T2_C/T = 0.
 * Timer2 is not started. AUXR.T2R = 0.
 * 
 * @param pins Pin configuration from uart1_pins_t enum
 * 
 * @note Must be called before starting UART communication
 * 
 * @ingroup uart1_mode1_timer2_12T
 */
void uart1_mode1_timer2_init(uart1_pins_t pins);

/**
 * @brief Start UART1 communication with standart baudrate value
 * 
 * @ingroup uart1_mode1_timer2_12T
 * 
 * @param baudrate uart1_mode1_timer2_12t_baudrate_t Baudrate selection from uart1_mode1_timer2_12t_baudrate_t enum
 * 
 * @note Before calling this function, uart1_mode1_timer2_init() must be called.
 * @note Enum contains standard baudrates with precalculated THTL values for 12T mode
 */
void uart1_mode1_timer2_start(const uart1_mode1_timer2_12t_baudrate_t baudrate);
/**
 * @brief Stop UART1 communication and disable Timer2
 * 
 * @ingroup uart1_mode1_timer2_12T
 * 
 * @warning Calling this function will terminate any ongoing communication
 */
void uart1_mode1_timer2_stop();

void uart1_mode1_timer2_send_byte(uint8_t data);

void uart1_mode1_timer2_receive_byte(uint8_t *data);

#endif