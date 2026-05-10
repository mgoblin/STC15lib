#ifndef STC15_TIMERH
#define STC15_TIMERH

/**
 * @file timer_common.h
 * @defgroup timer_common Timer configuration reading
 * 
 * @brief Gets config from timers.
 * 
 * @details This module contains reading mode and divider
 * from configured timer or counter routines
 * 
 * @author Michael Golovanov
 */

#include <bits.h>
#include <timer_structs.h>

/** @name Timer0
 *  Timer0 routines 
 */
///@{
/**
 * @brief Get mode for timer0.
 * 
 * @return timer0 mode in range from 0 to 3
 * 
 * @ingroup timer_common
 */
#define get_timer0_mode() (TMOD & 0x03)

/**
 * @brief Get clock divider for timer0. 
 * 
 * @return timer0 clock divider
 * 
 * @ingroup timer_common
 */
#define get_timer0_clock_divider() (test_if_bit_cleared(AUXR, SBIT7) ? T12 : T1)
///@}

/** @name Timer2
 *  Timer2 routines 
 */
///@{
/**
 * Get mode for timer2.
 * 
 * @return timer2 mode. Timer2 have only mode0.
 * 
 * @ingroup timer_common
 */
#define get_timer2_mode() (0)

/**
 * Get clock divider for timer2. 
 * 
 * @return timer2 clock divider
 * 
 * @ingroup timer_common
 */
#define get_timer2_clock_divider() (test_if_bit_set(AUXR, SBIT2) ? T1 : T12)
///@}

#endif