#ifndef STC15_UART1MODE3_T21H
#define STC15_UART1MODE3_T21H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <frequency.h>
#include <interrupt.h>
#include <uart1_9bit_shared.h>

/**
 * @file uart1_mode3_timer2_1T.h
 * 
 * @defgroup uart1_mode3_timer2_1T  UART1 Mode 3 with Timer2 1T
 * 
 * @details
 * Functions and data structures for UART1 communication in Mode 3 
 * with Timer2 1T as baudrate generator. 
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
 * THTL = 65536 - Sysclk/(4 * baudrate).
 * Sysclk = master clock frequency / frequency divder.
 * 
 * THTL value is precalulated for standard baudrates with none freq divider.
 * 
 * In UART1 Mode 3, three sets of RxD/TxD pins can be used: 
 * RxD on P3.0/TxD on P3.1, RxD on P3.6/TxD on P3.7 and 
 * RxD on P1.6/TxD on P1.7.
 * 
 * Typical usage:
 * ```c
 * uart1_mode3_timer2_1T_init(RxD_P30_TxD_P31);
 * uart1_mode3_timer2_1T_start(baudrate_9600);
 * 
 * for (;;)
 * {
 *  // Send or receive data
 * }
 * 
 * ``` 
 * 
 * @see uart1_send_9bit()
 * @see uart1_receive_9bit()
 * @see is_uart1_send_byte_complete()
 * @see is_uart1_receive_byte_complete()
 * 
 * @author Michael Golovanov
*/


#endif