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
 * 
 * Call this method after timer2 is initialized and MCU clock frequency divider scale is set.
 * 
 * @param ticks uint16_t timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_ticks_to_Hz(ticks) (timer_ticks_to_Hz(ticks, get_timer2_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Converts frequency to ticks for timer2 mode0. 
 * @details Call this method after timer2 is initialized and MCU clock frequency divider scale is set.
 * 
 * @warning On ticks uint16_t overflow returns 0 
 * 
 * @param frequency uint32_t frequency value in Hz. Should not be 0;
 * 
 * @return uint16_t timer2 ticks corresponding to given frequency value or 0 on result overflow
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_Hz_to_ticks(frequency) (timer_Hz_to_ticks(frequency, get_timer2_clock_divider(), get_frequency_divider_scale()))
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


/** @name timer start for frequency and ms
 *  Start Timer for ms or frequency  
 */
///@{

/**
 * @brief Start timer2 in mode 0 with ms duration
 * 
 * @param ms uint16_t timer overflow duration
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_start_ms(ms)                       \
do                                                      \
{                                                       \
    uint16_t ticks = timer2_mode0_ms_to_ticks(ms);      \
    timer2_mode0_start(ticks);                          \
} while (0);

/**
 * @brief Start timer2 in mode 0 with Hz frequency
 * 
 * @param freq uint32_t timer overflow frequency in Hz
 * 
 * @ingroup timer2_mode0_to_ms
 */
#define timer2_mode0_start_Hz(freq)                     \
do                                                      \
{                                                       \
    uint16_t ticks = timer2_mode0_Hz_to_ticks(freq);    \
    timer2_mode0_start(ticks);                          \
} while (0);


///@}


#endif