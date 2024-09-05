#ifndef STC15_TIMERH
#define STC15_TIMERH

/**
 * @file timer.h
 * @defgroup timer Timer
 * @details Functions and data structures for timers.
 * 
 * This module supports two generar purpose timers Timer0 and Timer1.
 * Each timer can work as COUNTER or TIMER. Counter increments on external singnal 
 * (like pin 1/0 change state). Input of timer is system clock.
 * 
 * 8051 chips timer has 4 modes
 * * mode0 - 8-bit timer/counter with 5-bit prescaler (13 bit timer)
 * * mode1 - 16-bit timer/counter
 * * mode2 - 8-bit auto reload timer/counter
 * * mode3 - The function depends on Timer0 or Timer1
 * 
 * This module version supports only mode0 for timer. 
 * Other timer modes and counter mode does not implements yet.
 * Timer interrups does not implements yet.    
 *    
 * @author Michael Golovanov
 */

#include <stdint.h>

/**
 * Timers enum
 */
typedef enum {
    /// Timer0
    TIMER0,
    /// Timer1
    TIMER1
} timer_id;

/**
 * Initialize mode0 for timer. Set TMOD bits.
 * 
 * @param timerid TIMER0 or TIMER1
 * 
 * @ingroup timer
 */
void timer_mode0_init(const timer_id timerid);

/**
 * @brief Run timer and wait  timer not finished.
 * @details Before run timer_mode0_init should be called. After run program flow blocked 
 * until timer does not finished.
 * 
 * @param timerid TIMER0 or TIMER1
 * @param tl_value timer interval prescaler (high 5 bits)
 * @param th_value timer interval prescaler (low 8 bits)
 * 
 * @ingroup timer 
 */
void timer_mode0_run_and_wait(const timer_id timerid, uint8_t tl_value, uint8_t th_value);

#endif