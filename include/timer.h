#ifndef STC15_TIMERH
#define STC15_TIMERH

#include <stdbool.h>
#include <bits.h>

#include <timer_structs.h>
#include <timer0.h>

/**
 * @file timer.h
 * @defgroup timer Timer
 * @details Functions and data structures for timers.
 * 
 * This module supports general purpose timer Timer0 and Timer2.
 * Each timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * 8051 chips timer has 4 modes
 * * mode0 - 13-Bit Auto-Reload Timer/Counter
 * 
 * For mode0:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * Timer0 mode0 can be used in sync (main prorgam flow blocked until timer overloaded) 
 * and interrupt (call interrupt handler on timer overloaded) modes.
 * 
 * Timer2 mode0 can be used only in interrupt mode. 
 * 
 * If Timer2 using as general purpose timer then UART can not be used.
 * 
 * CPU frequency change biased timer delays.
 *  
 * This module version supports only timer0, timer2 mode0 12T and 1T for timer0. 
 * Other timers, modes and counter mode does not implements yet.
 *    
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <timer_structs.h>


/**
 * Get timer2 mode
 * 
 * @return timer2 mode. Timer2 have only mode0.
 * 
 * @ingroup timer
 */
#define get_timer2_mode() (0)

/**
 * Get timer2 clock divider
 * 
 * @return timer2 clock divider
 * 
 * @ingroup timer
 */
#define get_timer2_clock_divider() (get_bit(AUXR, 2) == 0 ? T12 : T1)

/**
 * Get output to pin P3.0 output flag enabled value
 * 
 * @return true if output enabled oterwise false
 * 
 * @ingroup timer
 */
#define is_timer2_P30_output_enabled() (get_bit(INT_CLKO, 2) > 0)

//============================== Timer2 mode0 declarations begin ==========================
/**
 * @brief Initialize mode0 12T for timer2. Set AUXR bits.
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/12.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer
 */
void timer2_mode0_12T_init();

/**
 * @brief Initialize mode0 1T for timer2. Set AUXR bits.
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/1.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer
 */
void timer2_mode0_1T_init();

/**
 * @brief Run timer2 mode0 with interrupt support.
 * @details Before run timer2_mode0_12T_init or timer2_mode0_1T_init should be called. 
 * After run program flow not blocked and interrupt will generated when timer is overloaded.
 * Interrupt handler void timer2ISR(void) __interrupt(12) should be defined in user code.
 * Timer rerun after overloaded and interuppt handler called. 
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
 * 
 * @ingroup timer
 */
void timer2_mode0_start(uint8_t th_value, uint8_t tl_value);

/**
 * @brief Stop timer2 mode0 with interrupt support.
 * @details Before stop timer2_mode0_start should be called. 
 * 
 * @ingroup timer
 */
void timer2_mode0_stop();

/**
 * @brief Enable output of meandr with timer times on P3.0 pin.
 * @details By default output is disabled
 * 
 * @param enable if true output is enabled otherwise output is disabled 
 * 
 * @ingroup timer
 */
void timer2_mode0_enableP30_output(bool enable);

//============================== Timer2 mode0 declarations end ============================

#endif