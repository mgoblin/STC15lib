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
 * @brief Converts ticks to timer overflow frequency for timer0 mode3.
 * @details The output frequency = (SYSclk/timer_clock_divider)/(1 + ticks).
 * 
 * Call this method after timer0 is initialized and MCU clock frequency divider scale is set.
 * 
 * uint16 ticks used in timer mode 0, 1, 3.
 * For timer mode2 (8 bit autoreladable timer) ticks can be in 0..255 range. 
 * 
 * @param ticks uint16_t timer ticks count to covert
 * 
 * @return float frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer0_mode3_to_ms
 */
#define timer0_mode3_ticks_to_Hz(ticks) (timer_ticks_to_Hz(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Converts frequency to ticks for timer0 mode3. 
 * @details Call this method after timer0 is initialized and MCU clock frequency divider scale is set.
 * 
 * @warning on result overflow returns 0. Be careful.
 * 
 * @param frequency uint32_t frequency value in Hz. Should not be 0;
 * 
 * @return uint16_t timer0 ticks corresponding to frequency value or 0 on result overflow
 * 
 * @ingroup timer0_mode3_to_ms
 */
#define timer0_mode3_frequency_to_ticks(frequency) (timer_frequency_to_ticks(frequency, get_timer0_clock_divider(), get_frequency_divider_scale()))

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