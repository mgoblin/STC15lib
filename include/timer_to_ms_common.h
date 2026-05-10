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
 * @brief Convert 16-bit timer ticks count to ms
 * 
 * @attention This routine use integer division math and therefore have 
 * a calculation inaccuracy.
 * 
 * @warning This method doesnt analyze corner cases and overflow of results. 
 * Be careful. 
 * For example, in timer 12T mode0 and MCU frequency divider scale equals to 0 
 * correct ticks values is 1000..65535.
 * 
 * @param ticks uint16_t ticks count. Range 7...65535
 * @param timer_divider timer_clock_divider_t 1T or 12T timer clock divider
 * @param frequency_divider_scale uint8_t MCU frequency divider scale 0..7
 * 
 * @return uint16_t milliseconds time corresponing to timer ticks. Range 0..9043
 * 
 * @ingroup timer_to_ms
 */
uint16_t timer_ticks_to_ms( uint16_t ticks, timer_clock_divider_t timer_divider, uint8_t frequency_divider_scale);

/**
 * @brief Converts milliseconds to timer ticks (unsafe conversion)
 * 
 * @details This function converts a given time duration in milliseconds to the corresponding 
 * 16-bit timer reload/tick count based on the MCU's clock frequency, timer clock divider (T1 or T12), 
 * and the system frequency divider scale. The calculation assumes:
 *   - Timer operates in one of the standard modes (e.g., Mode 1 - 16-bit timer).
 *   - The timer counts up from the initial value to 0xFFFF (65535), so the number of ticks 
 *     before overflow is (65536 - initial_value).
 * 
 * The formula used:
 *   ticks = ms × (MCU_frequency / 1000) / timer_clock_divider
 *   where:
 *     - MCU_frequency = MAIN_Fosc >> frequency_divider_scale
 *     - timer_clock_divider = 1 for 1T mode, 12 for 12T mode
 * 
 * @warning This function does **not** perform safety checks for overflow beyond `uint16_t` range.
 * If the computed tick count exceeds 65535, it will be clamped to 0. It is the caller's responsibility
 * to ensure that input values result in valid tick counts within the allowable timer range.
 * 
 * @warning Inaccuracies may arise due to integer division truncation, especially at higher 
 * frequency divider scales or very small millisecond values.
 * 
 * @param ms                    uint16_t Time duration in milliseconds [1..~9000 depending on clock]
 * @param divider               timer_clock_divider_t Clock divider for the timer: T1 (1T mode) or T12 (12T mode)
 * @param frequency_divider_scale uint8_t System clock divider scale (0..7), used as shift right amount on MAIN_Fosc
 * 
 * @return uint16_t             Number of timer ticks corresponding to the input time.
 *                              Returns 0 if the result overflows uint16_t range.
 * 
 * @note Example:
 *   For MAIN_Fosc = 11059200 Hz, frequency_divider_scale = 0, divider = T12 (12):
 *     mcu_freq_ms = 11059200 / 1000 = 11059
 *     timer_freq_ms = 11059 / 12 ≈ 921
 *     ms = 10 → ticks = 10 * 921 = 9210
 * 
 * @ingroup timer_to_ms
 */
 uint16_t timer_ms_to_ticks_usafe(uint16_t ms, timer_clock_divider_t divider, uint8_t frequency_divider_scale);// (ms * ((get_master_clock_frequency_high_part() + 26) >> get_frequency_divider_scale()) / timer_clock_divider)

#endif
