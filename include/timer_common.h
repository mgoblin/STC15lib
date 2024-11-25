#ifndef STC15_TIMERH
#define STC15_TIMERH

/**
 * @file timer_common.h
 * @defgroup timer_common Timer common
 * @details Common functions and data structures for timers.
 * 
 * @author Michael Golovanov
 */

#include <bits.h>
#include <timer_structs.h>

//============================== Timer0 get mode, divider, pins declarations start ========
/**
 * @brief Get timer0 mode
 * 
 * @return timer0 mode in range from 0 to 3
 * 
 * @ingroup timer_common
 */
#define get_timer0_mode() (TMOD & 0x03)

/**
 * @brief Get timer0 clock divider
 * 
 * @return timer0 clock divider
 * 
 * @ingroup timer_common
 */
#define get_timer0_clock_divider() (test_if_bit_cleared(AUXR, 7) ? T12 : T1)

/**
 * @brief Enable output of meandr with timer interval on P3.5 pin.
 * @details By default output is disabled
 * 
 * @param enable bool if true output is enabled otherwise output is disabled 
 * 
 * @ingroup timer0
 */

/**
 * Get timer2 mode
 * 
 * @return timer2 mode. Timer2 have only mode0.
 * 
 * @ingroup timer_common
 */
#define get_timer2_mode() (0)

/**
 * Get timer2 clock divider
 * 
 * @return timer2 clock divider
 * 
 * @ingroup timer_common
 */
#define get_timer2_clock_divider() (test_if_bit_cleared(AUXR, 2) ? T12 : T1)

#endif