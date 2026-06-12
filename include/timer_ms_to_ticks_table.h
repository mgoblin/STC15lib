#ifndef STC15_TIMER_TO_MS_TABLEH
#define STC15_TIMER_TO_MS_TABLEH

/**
 * @file timer_ms_to_ticks_table.h
 * @defgroup timer_ms_to_ticks_table Timer to milliseconds conversion table
 * @details Functions and data structures for converting milliseconds to timer ticks
 *          using precalculated lookup tables for efficient runtime conversion.
 * 
 * This module provides a table-based approach for converting 1 millisecond durations
 * to timer tick counts, accounting for different clock divider modes (1T and 12T).
 * The conversion uses precalculated values stored in lookup tables to avoid
 * expensive runtime calculations.
 * 
 * The lookup tables contain precomputed tick values for 1ms delays at various
 * system clock frequencies and divider settings. The appropriate table is selected
 * based on the timer's clock divider setting (T1 for 1T mode or T12 for 12T mode).
 * 
 * @note The precalculated values are optimized for common crystal frequencies
 *       and may have slight variations due to rounding. For exact calculations,
 *       use the dynamic conversion functions in timer_to_ms_common.h instead.
 * 
 * @see timer_to_ms_common.h - Dynamic millisecond to ticks conversion functions
 * @see timer_structs.h - Timer clock divider definitions
 * @see frequency.h - System clock frequency management
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <timer_common.h>

/**
 * @brief Convert 1 millisecond to timer ticks based on clock divider
 * 
 * This function looks up the precalculated tick count for a 1 millisecond delay
 * based on the provided clock divider setting. It uses different lookup tables
 * for 1T mode (one clock cycle per tick) and 12T mode (twelve clock cycles per tick).
 * 
 * The function selects the appropriate lookup table based on the divider parameter
 * and uses the current system clock frequency scale (from CLK_DIV register) to
 * index into the table. This provides O(1) conversion time without runtime math.
 * 
 * @param divider timer_clock_divider_t Clock divider setting:
 *                - T1 (1): 1T mode, timer increments once per clock cycle
 *                - T12 (12): 12T mode, timer increments once per 12 clock cycles
 * 
 * @return uint16_t Number of timer ticks corresponding to 1 millisecond delay
 *                  for the given clock divider setting
 * 
 * @note The returned value is precalculated and may have small approximation errors
 *       compared to exact mathematical calculation. Typical error is less than 1%.
 * 
 * @note The function uses get_frequency_divider_scale() internally to select the
 *       appropriate array index based on the current system clock divider.
 * 
 * @ingroup timer_ms_to_ticks_table
*/
uint16_t timer_1ms_to_ticks(timer_clock_divider_t divider);

#endif
