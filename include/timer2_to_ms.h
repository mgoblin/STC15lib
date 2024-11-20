#ifndef STC15_TIMER0_TO_MSH
#define STC15_TIMER0_TO_MSH

/**
 * @file timer2_to_ms.h
 * @defgroup timer2_to_ms Timer2 Aux
 * @details Functions and data structures for converting timer ticks 
 * to frequency and times for timer2.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer2_mode0.h>
#include <timer_common.h>
#include <timer_to_ms_common.h>

/** @name tick to frequency conversions
 *  Timer ticks to overlow frequency and vice versa convertions 
 */
///@{

/**
 * @brief Convert ticks to timer frequency for timer2 multiplied by 100.
 * @details The output frequency = (SYSclk/timer_clock_divider)/((65536-ticks) * 2).
 * Multiplication by 100 is used for get frequency value without using float numbers.
 * 
 * Call this method after timer2 is initialized and MCU clock frequency divider scale is set.
 * 
 * @param ticks uint16_t timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer2_to_ms
 */
#define timer2_uint16_ticks_to_freq100(ticks) (timer_uint16_ticks_to_freq100(ticks, get_timer2_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Unsafe approximation timer2 frequency corresponding to ticks. 
 * @details 
 * ticks = get_master_clock_frequency() / (2 * get_timer2_clock_divider() * frequency))
 * 
 * Call this method after timer2 is initialized and MCU clock frequency divider scale is set.
 * 
 * <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param frequency uint32_t frequency value in Hz. Should not be 0;
 * 
 * @return uint16_t timer0 ticks corresponding to frequency value
 * 
 * @ingroup timer2_to_ms
 */
#define timer2_frequency_to_ticks_unsafe(frequency) (timer_frequency_to_ticks_unsafe(frequency, get_timer2_clock_divider(), get_frequency_divider_scale()))

///@}

/** @name UART baud rate to ticks
 *  UART baud rate to timer ticks to overlow frequency and vice versa convertions 
 */
///@{

/**
 * @brief Calculate timer2 ticks for UART baudrate
 * @details Adapter for mcu frequency divider
 * 
 * @param uart_baudrate uint16_t UART baudrate
 * 
 * @return uint16_t timer2 ticks count for UART baudrate
 * 
 * @ingroup timer2_to_ms
 */
#define timer2_mode0_baudrate_to_ticks(uart_baudrate) ((get_master_clock_frequency() >> get_frequency_divider_scale())/4/uart_baudrate - 1)

///@}

#endif