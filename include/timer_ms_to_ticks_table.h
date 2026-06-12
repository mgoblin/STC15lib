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
 * @brief Initializes Timer0 for 1 millisecond delay using precalculated ticks
 
 * @note Must be called before using timer0_1ms_delay() to ensure correct
 *       timer configuration for the current system clock settings.
 * @note Disables Timer0 interrupt during initialization to prevent
 *       unwanted interrupt service routine execution.
 * 
 * @see get_frequency_divider_scale() - Gets current frequency scale index
 * @see get_timer0_clock_divider() - Gets Timer0 clock divider setting
 * @see timer0_1ms_delay() - Performs the actual 1ms delay
 * @see precalc_1t_ticks - Lookup table for 1T mode tick values
 * @see precalc_12t_ticks - Lookup table for 12T mode tick values
 */
void timer0_1ms_delay_init();

/**
 * @brief Executes a 1 millisecond delay using Timer0
 * @details Starts Timer0 and waits for the overflow flag (TF0) to be set,
 *          indicating that the configured 1ms time interval has elapsed.
 *          The timer is configured by timer0_1ms_delay_init() with the
 *          appropriate reload values for the system clock frequency.
 * 
 * @note This is a blocking function that waits in a polling loop until
 *       the timer overflow occurs.
 * @note Timer0 must be initialized with timer0_1ms_delay_init() before
 *       calling this function.
 * 
 * @see timer0_1ms_delay_init() - Initializes Timer0 for 1ms delay
 * @see TF0 - Timer0 overflow flag
 * @see TR0 - Timer0 run control bit
 */
void timer0_1ms_delay();

#endif
