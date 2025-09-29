#ifndef STC15_UART1MODE1H
#define STC15_UART1MODE1H

/**
 * @file uart1_mode1_timer2_12T.h
 * @defgroup uart1_mode1_timer2_12T  UART1 Mode 1 with Timer2 12T
 * 
 * @details 
 * Functions and data structures for UART1 communication in Mode 1 
 * with Timer2 12T as baudrate generator.
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

void uart1_mode1_timer2_init(uart1_pins_t pins);

void uart1_mode1_timer2_start(const uint32_t baudrate);
void uart1_mode1_timer2_stop();

#endif