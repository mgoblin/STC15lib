#ifndef STC15_TIMER0_MODE3_TO_MSH
#define STC15_TIMER0_MODE3_TO_MSH

/**
 * @file timer0_mode3_to_ms.h
 * @defgroup timer0_mode3_to_ms Timer0 Mode3 ticks to duration/frequency convertions
 * @details Functions and data structures for converting timer ticks 
 * to frequency and times for timer0 mode3.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer0_mode3.h>
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
 * @ingroup timer0_mode3_to_ms
 */
#define timer0_mode3_ticks_to_freq100(ticks) (timer_uint16_ticks_to_freq100(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

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
 * @ingroup timer0_mode3_to_ms
 */
#define timer0_mode3_frequency_to_ticks_unsafe(frequency) (timer_frequency_to_ticks_unsafe(frequency, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert ticks count to ms
 * 
 * @param ticks uint16_t ticks count. Range 7...65535
 * 
 * @return milliseconds time corresponing to timer ticks. Range 0..9043
 * 
 * @ingroup timer0_mode3_to_ms
 */
#define timer0_mode3_ticks_to_ms(ticks) (timer_16bit_ticks_to_ms(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert milliseconds to timer0 ticks.
 * 
 * @param ms uint16_t ms to convert. Range is 1..~9000
 * 
 * @return uint16_t     Number of timer ticks corresponding to the input time.
 *                      Returns 0 if the result overflows uint16_t range.
 * 
 * 
 * @ingroup timer0_mode3_to_ms
 */
#define timer0_mode3_ms_to_ticks(ms) (timer_ms_to_ticks(ms, get_timer0_clock_divider(), get_frequency_divider_scale()))

///@}

#endif