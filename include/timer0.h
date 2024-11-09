#ifndef STC15_TIMER0H
#define STC15_TIMER0H

#include <sys.h>
#include <bits.h>
#include <interrupt.h>

#include <stdint.h>
#include <stdbool.h>

#include <timer_structs.h>

/**
 * Get timer0 mode
 * 
 * @return timer0 mode in range from 0 to 3
 * 
 * @ingroup timer
 */
#define get_timer0_mode() (TMOD & 0x03)

/**
 * Get timer0 clock divider
 * 
 * @return timer0 clock divider
 * 
 * @ingroup timer
 */
#define get_timer0_clock_divider() (get_bit(AUXR, 7) == 0 ? T12 : T1)

/**
 * Get output to pin P3.5 output flag enabled value
 * 
 * @return true if output enabled oterwise false
 * 
 * @ingroup timer
 */
#define is_timer0_P35_output_enabled() (INT_CLKO & 0x01 > 0)

//============================== Timer0 mode0 declarations begin ==========================

/**
 * @brief Disable timer on INT0(P3.2) pin is low
 * @details if you wand resore default timer behaviour indepned of INT0 state
 * reinit timer should be done 
 */
# define timer0_enable_on_pinINT0_high() (bit_set(TMOD, 3))

/**
 * Initialize mode0 12T for timer0 in mode0. Set TMOD bits.
 * 
 * @ingroup timer
 */
void timer0_mode0_12T_init();

/**
 * Initialize mode0 1T for timer0. Set TMOD bits.
 * 
 * @ingroup timer
 */
void timer0_mode0_1T_init();

/**
 * @brief Run timer0 mode0 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode0_12T_init or timer0_mode0_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * Timer overloading occurs on th_value and tl_value is 0xff, therefore 
 * maximal timer interval corresponds to th_value and tl_value equals 0 
 * 
 * Dont mix call of timer0_mode0_run_once_and_wait with
 * timer0_mode0_start/timer0_mode0_stop calls.
 * 
 * For mode0 and mode1 implementation is the same.
 * 
 * @param th_value timer interval high part (high 8 bits)
 * @param tl_value timer interval low part (low 8 bits)
 * 
 * @ingroup timer 
 */
void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value);

/**
 * @brief Run timer0 mode0 with interrupt support.
 * @details Before run timer0_mode0_12T_init or timer0_mode0_1T_init should be called. 
 * After run program flow not blocked and interrupt will generated when timer is overloaded.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * Timer rerun after overloaded and interuppt handler called. 
 * Dont mix call timer0_mode0_start call with 
 * void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value) call
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
 * 
 * @ingroup timer
 */
void timer0_mode0_start(uint8_t th_value, uint8_t tl_value);

/**
 * @brief Stop timer0 mode0 with interrupt support.
 * @details Before stop timer0_mode0_start should be called. 
 * Dont mix timer0_mode0_stop call with
 * void timer0_mode0_run_once_and_wait(uint8_t th_value, uint8_t tl_value) call 
 * 
 * @ingroup timer
 */
void timer0_mode0_stop();

/**
 * @brief Enable output of meandr with timer times on P3.5 pin.
 * @details By default output is disabled
 * 
 * @param enable if true output is enabled otherwise output is disabled 
 * 
 * @ingroup timer
 */
void timer0_mode0_enableP35_output(bool enable);

//============================== Timer0 mode0 declarations end ============================

//============================== Timer0 mode1 declarations begin ==========================

/**
 * Initialize mode1 12T for timer0 in mode1. Set TMOD and AUXR bits.
 * 
 * @ingroup timer
 */
void timer0_mode1_12T_init();

// /**
//  * Initialize mode0 1T for timer0 in mode1. Set TMOD bits.
//  * 
//  * @ingroup timer
//  */
// TODO void timer0_mode1_1T_init();

/**
 * @brief Run timer0 mode1 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode1_12T_init or timer0_mode1_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * Timer overloading occurs on th_value and tl_value is 0xff, therefore 
 * maximal timer interval corresponds to th_value and tl_value equals 0 
 * 
 * Dont mix call of timer0_mode0_run_once_and_wait with
 * timer0_mode1_start/timer0_mode1_stop calls.
 * 
 * For mode0 and mode1 implementation is the same.
 * 
 * @param th_value timer interval high part (high 8 bits)
 * @param tl_value timer interval low part (low 8 bits)
 * 
 * @ingroup timer 
 */
void timer0_mode1_run_once_and_wait(uint8_t th_value, uint8_t tl_value);

//============================== Timer0 mode1 declarations end ============================


#endif