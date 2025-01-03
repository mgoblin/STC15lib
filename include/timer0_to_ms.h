#ifndef STC15_TIMER0_TO_MSH
#define STC15_TIMER0_TO_MSH

/**
 * @file timer0_to_ms.h
 * @defgroup timer0_to_ms Timer0 Aux
 * @details Functions and data structures for converting timer ticks 
 * to frequency and times for timer0.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer0_mode0.h>
#include <timer_common.h>
#include <timer_to_ms_common.h>

/** @name frequency and ticks
 *  Timer ticks to frequency and vice versa convertions  
 */
///@{

/**
 * @brief Convert ticks to timer frequency for timer0 multiplied by 100.
 * @details The output frequency = (SYSclk/timer_clock_divider)/((65536-ticks) * 2).
 * Multiplication by 100 is used for get frequency value without using float numbers.
 * 
 * Call this method after timer0 is initialized and MCU clock frequency divider scale is set.
 * 
 * uint16 ticks used in mode 0, 1, 3.
 * Low byte of ticks is used in mode 2. 
 * 
 * @param ticks uint16_t timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer0_to_ms
 */
#define timer0_uint16_ticks_to_freq100(ticks) (timer_uint16_ticks_to_freq100(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Unsafe approximation timer0 frequency corresponding to ticks. 
 * @details 
 * ticks = get_master_clock_frequency() / (2 * get_timer0_clock_divider() * frequency))
 * 
 * Call this method after timer0 is initialized and MCU clock frequency divider scale is set.
 * 
 * <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param frequency uint32_t frequency value in Hz. Should not be 0;
 * 
 * @return uint16_t timer0 ticks corresponding to frequency value
 * 
 * @ingroup timer0_to_ms
 */
#define timer0_frequency_to_ticks_unsafe(frequency) (timer_frequency_to_ticks_unsafe(frequency, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert ticks count to ms
 * @details <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param ticks uint16_t ticks count
 * 
 * @return milliseconds time corresponing to timer ticks
 * 
 * @ingroup timer0_to_ms
 */
#define timer0_ticks_to_ms_usafe(ticks) (timer_ticks_to_ms_usafe(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert milliseconds to timer0 ticks.
 * @details 
 * 1 ms = ((get_master_clock_frequency_high_part() + 26) >> get_frequency_divider_scale()) / timer_clock_divider
 * 
 * This routine doesnt check overflows. Its unsafe.
 * 
 * @param ms uint16_t ms to convert
 * 
 * @return uint16_t ticks count for milliseconds
 * 
 * 
 * @ingroup timer0_to_ms
 */
#define timer0_ms_to_ticks_usafe(ms) (timer_ms_to_ticks_usafe(ms, get_timer0_clock_divider()))

///@}

#endif