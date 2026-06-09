#ifndef STC15_TIMER0_MODE2_TO_MSH
#define STC15_TIMER0_MODE2_TO_MSH

/**
 * @file timer0_mode2_to_ms.h
 * @defgroup timer0_mode2_to_ms Timer0 Mode2 ticks to duration/frequency convertions
 * @details Functions and data structures for converting timer ticks 
 * to frequency and times for timer0 mode2.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer0_mode2.h>
#include <timer_common.h>
#include <timer_to_ms_common.h>

/** @name frequency and ticks
 *  Timer ticks to frequency and vice versa convertions  
 */
///@{

/**
 * @brief Converts ticks to timer overflow frequency for timer0 mode2.
 * @details The output frequency = (SYSclk/timer_clock_divider)/(1 + ticks) .
 * 
 * Call this method after timer0 is initialized and MCU clock frequency divider scale is set.
 * 
 * uint16 ticks used in timer mode 0, 1, 3.
 * For timer mode2 (8 bit autoreladable timer) ticks can be in 0..255 range. 
 * 
 * @param ticks uint16_t timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer0_mode2_to_ms
 */
#define timer0_mode2_ticks_to_Hz(ticks) (timer_ticks_to_Hz(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Converts frequency corresponding to ticks for timer0 mode2. 
 * @details Call this method after timer0 is initialized and MCU clock frequency divider scale is set.
 * 
 * @warning On result iverflow returns 0. Be careful. 
 * 
 * @param frequency uint32_t frequency value in Hz. Should not be 0;
 * 
 * @return uint8_t timer0 ticks corresponding to frequency value
 * 
 * @ingroup timer0_mode2_to_ms
 */
#define timer0_mode2_Hz_to_ticks(frequency) (timer_Hz_to_ticks_8bit(frequency, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert ticks count to microseconds
 * 
 * @param ticks uint8_t ticks count. 
 * 
 * @return uint16_t microseconds time corresponing to timer ticks. 
 * 
 * @ingroup timer0_mode2_to_ms
 */
#define timer0_mode2_ticks_to_mcs(ticks) (timer_8bit_ticks_to_mcs(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert milliseconds to timer0 ticks.
 * 
 * @param ms uint16_t ms to convert. Range is 1..~9000
 * 
 * @return uint16_t     Number of timer ticks corresponding to the input time.
 *                      Returns 0 if the result overflows uint16_t range.
 * 
 * 
 * @ingroup timer0_mode2_to_ms
 */
#define timer0_mode2_ms_to_ticks(ms) (timer_ms_to_ticks(ms, get_timer0_clock_divider(), get_frequency_divider_scale()))

///@}

/** @name timer start for frequency and ms
 *  Start Timer for ms or frequency  
 */
///@{

/**
 * @brief Start timer0 in mode 2 with ms duration
 * 
 * @param ms uint8_t timer overflow duration
 * 
 * @ingroup timer0_mode2_to_ms
 */
#define timer0_mode2_start_ms(ms)                       \
do                                                      \
{                                                       \
    uint8_t ticks = timer0_mode2_ms_to_ticks(ms);       \
    timer0_mode2_start(ticks);                          \
} while (0);

/**
 * @brief Start timer0 in mode 2 with Hz frequency
 * 
 * @param freq uint32_t timer overflow frequency in Hz
 * 
 * @ingroup timer0_mode2_to_ms
 */
#define timer0_mode2_start_Hz(freq)                     \
do                                                      \
{                                                       \
    uint8_t ticks = timer0_mode2_Hz_to_ticks(freq);     \
    timer0_mode2_start(ticks);                          \
} while (0);


///@}

#endif