#ifndef STC15_TIMER2_MODE0_TO_MSH
#define STC15_TIMER2_MODE0_TO_MSH

/**
 * @file timer2_mode0_to_ms.h
 * @defgroup timer2_mode0_to_ms Timer2 Mode0 ticks to duration/frequency convertions
 * @details Functions and data structures for converting timer2 ticks 
 * to duration/frequency and vice versa.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer2_mode0.h>
#include <timer_common.h>
#include <timer_to_ms_common.h>

/** @name ticks to frequency conversions
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
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_ticks_to_freq100(ticks) (timer_ticks_to_Hz(ticks, get_timer2_clock_divider(), get_frequency_divider_scale()))

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
 * @return uint16_t timer2 ticks corresponding to frequency value
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_frequency_to_ticks_unsafe(frequency) (timer_frequency_to_ticks_unsafe(frequency, get_timer2_clock_divider(), get_frequency_divider_scale()))
///@}

/** @name ticks to duration conversions
 *  Timer ticks to timer overlow duration and vice versa convertions 
 */
///@{

/**
 * @brief Convert ticks count to ms
 * @details <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param ticks uint16_t ticks count
 * 
 * @return milliseconds time corresponing to timer ticks
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_ticks_to_ms(ticks) (timer_16bit_ticks_to_ms(ticks, get_timer2_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert milliseconds to timer2 ticks.
 * @details 
 * 
 * This routine doesnt check overflows. Its unsafe.
 * 
 * @param ms uint16_t ms to convert
 * 
 * @return uint16_t ticks count for milliseconds
 * 
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_ms_to_ticks(ms) (timer_ms_to_ticks(ms, get_timer2_clock_divider(), get_frequency_divider_scale()))
///@}

#endif