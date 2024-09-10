#ifndef STC15_TIMERH
#define STC15_TIMERH

/**
 * @file timer.h
 * @defgroup timer Timer
 * @details Functions and data structures for timers.
 * 
 * This module supports general purpose timer Timer0.
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * Input of timer is system clock.CPU frequency change biased timer delays.
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
 * Initialize mode0 for timer0. Set TMOD bits.
 * 
 * @ingroup timer
 */
void timer0_mode0_init();

/**
 * @brief Run timer and wait  timer not finished.
 * @details Before run timer0_mode0_init should be called. After run program flow blocked 
 * until timer does not finished.
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
 * 
 * @ingroup timer 
 */
void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value);

void timer0_mode0_start(uint8_t th_value, uint8_t tl_value);

void timer0_mode0_stop();

#endif