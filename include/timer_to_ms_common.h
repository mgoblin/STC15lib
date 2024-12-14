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
#include <timer_structs.h>
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
#define timer_uint16_ticks_to_freq100(ticks, timer_clock_divider, frequency_divider_scale) ((100 * get_master_clock_frequency() / (timer_clock_divider * (1 + (uint32_t)ticks))) >> frequency_divider_scale)

/**
 * @brief Convert timer frequency to ticks (unsafe operation)
 * @details Frequency to ticks is a reverse operation of ticks to frequency, 
 * 
 * Not all frequency ranges can be correctly coverted to ticks. This method doesnt carefully 
 * analyze frequency to ticks covertion correctness.
 * 
 * For 1T mode and frequency divider scale 0 minimal frequency is near 100Hz 
 * (11059200 / 2 / 100) = 55296 ticks and maximum frequency is near 5MHz 1.1 ticks
 * 
 * For 12T mode and frequency divider scale 0 minimal frequency is near 8Hz 
 * (11059200 / 2 / 12 / 8) = 57600 ticks and maximum frequency is near 400kHz
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

/**
 * @brief Convert ticks count to ms
 * @details <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param ticks uint16_t ticks count
 * @param timer_divider timer_clock_divider_t 1T or 12T timer clock divider
 * @param frequency_divider_scale uint8_t MCU frequency divider scale
 * 
 * @return milliseconds time corresponing to timer ticks
 * 
 * @ingroup timer_to_ms
 */
#define timer_ticks_to_ms_usafe(ticks, timer_divider, frequency_divider_scale) (((1UL + (uint32_t)ticks) / ((get_master_clock_frequency_high_part() / timer_divider) >> frequency_divider_scale)))

// 1T mode timer0 mode0 - ticks = time * SysClk - 1
// for 1 ms (10^-3) = get_master_clock_frequency_high_part()/10 - 1 = 11059 - 1 = 11058 = 0x2b32
// measurement is 0x2b4d, delta = 27
// get_master_clock_frequency_high_part()/10 + 26

/**
 * @brief Convert milliseconds to timer ticks.
 * @details 
 * 1 ms = ((get_master_clock_frequency_high_part() + 26) >> get_frequency_divider_scale()) / timer_clock_divider
 * 
 * This routine doesnt check overflows. Its unsafe.
 * 
 * @param ms uint16_t ms to convert
 * @param timer_clock_divider timer clock divider
 * 
 * @return uint16_t ticks count for milliseconds
 * 
 * @ingroup timer_to_ms
 */
uint16_t timer_ms_to_ticks_usafe(uint16_t ms, timer_clock_divider_t timer_clock_divider);

#endif
