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
 * 8051 chips timer has 4 modes
 * * mode0 - 16-Bit Auto-Reload Timer/Counter
 * 
 * For mode0:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * CPU frequency change biased timer delays.
 *  
 * This module version supports only mode0 12T for timer. 
 * Other timer modes and counter mode does not implements yet.
 *    
 * @author Michael Golovanov
 */

#include <stdint.h>

/**
 * Initialize mode0 12T for timer0. Set TMOD bits.
 * 
 * @ingroup timer
 */
void timer0_mode0_12T_init();

/**
 * @brief Run timer0 and wait timer not finished.
 * @details Before run timer0_mode0_12T_init should be called. After run program flow blocked 
 * until timer does not finished.
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
 * 
 * @ingroup timer 
 */
void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value);

/**
 * @brief Run timer0 with interrupt support.
 * @details Before run timer0_mode0_12T_init should be called. 
 * After run program flow not blocked and interrupt will generated when timer is finished.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined.
 * Timer rerun after finished. 
 * Dont mix timer0_mode0_start call with 
 * void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value) call
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
 * 
 * @ingroup timer
 */
void timer0_mode0_start(uint8_t th_value, uint8_t tl_value);

/**
 * @brief Stop timer0 with interrupt support.
 * @details Before stop timer0_mode0_start should be called. 
 * Dont mix timer0_mode0_stop call with
 * void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value) call 
 * 
 * @ingroup timer
 */
void timer0_mode0_stop();

#endif