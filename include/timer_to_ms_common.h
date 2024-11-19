#ifndef STC15_TIMER_TO_MS_COMMONH
#define STC15_TIMER_TO_MS_COMMONH

/**
 * @file timer_to_ms_common.h
 * @defgroup timer_to_ms Timer Aux common
 * @details Functions and data structures for converting timer ticks 
 * to frequency and times for timers.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer_to_ms_common.h>

/**
 * @brief Convert ticks to timer frequency multiplied by 100.
 * @details The output frequency = (SYSclk/timer_clock_divider)/((65536-ticks) * 2).
 * Multiplication by 100 is used for get frequency value without using float numbers.
 * 
 * uint16 ticks used in mode 0, 1, 3.
 * Low byte of ticks is used in mode 2. 
 * 
 * @param ticks uint16_t timer ticks count to covert
 * @param timer_clock_divider uint8_t timer clock divider T12 or T1
 * @param frequency_divider_scale uint8_t mcu frequency divider scale 0..7
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer_to_ms
 */
#define timer_uint16_ticks_to_freq100(ticks, timer_clock_divider, frequency_divider_scale) ((100 * get_master_clock_frequency() / ((timer_clock_divider << 1) * (1 + (uint32_t)ticks))) >> frequency_divider_scale)

/**
 * @brief Convert timer frequency to ticks (unsafe operation)
 * @details Frequency to ticks is a reverse operation of ticks to frequency, 
 * 
 * Not all frequency ranges can be correctly coverted to ticks. This method doesnt carefully 
 * analyze frequency to ticks covertion correctness.
 *   
 * @param frequency uint32_t frequency
 * @param timer_clock_divider uint8_t or timer_clock_divider_t enum T12 or T1 timer clock divider
 * @param frequency_divider_scale uint8_t mcu clock frequency diviver scale in range of [0..7]
 * 
 * @return uint16_t ticks count for input parameters 
 * 
 * @ingroup timer_to_ms
 */
#define timer_frequency_to_ticks_unsafe(frequency, timer_clock_divider, frequency_divider_scale) (((get_master_clock_frequency() >> 1) / (frequency * timer_clock_divider)) >> frequency_divider_scale)

#endif
