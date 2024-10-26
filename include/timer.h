#ifndef STC15_TIMERH
#define STC15_TIMERH

#include <stdbool.h>

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

/**
 * Get timer0 mode
 * 
 * @return timer0 mode in range from 0 to 3
 * 
 * @ingroup timer
 */
uint8_t get_timer0_mode();

/**
 * Get timer2 mode
 * 
 * @return timer0 mode. Timer2 have only mode0.
 * 
 * @ingroup timer
 */
uint8_t get_timer2_mode();

/**
 * Timer clock divider
 * 
 * @ingroup timer
 */
typedef enum TimerClockDivider
{
    /// Sysclk/1
    T1 = 1, 
    /// Sysclk/12
    T12 = 12
} timer_clock_divider;

/**
 * Get timer0 clock divider
 * 
 * @return timer0 clock divider
 * 
 * @ingroup timer
 */
timer_clock_divider get_timer0_clock_divider();

/**
 * Get timer2 clock divider
 * 
 * @return timer2 clock divider
 * 
 * @ingroup timer
 */
timer_clock_divider get_timer2_clock_divider();


//============================== Timer0 mode0 declarations begin ==========================
/**
 * Initialize mode0 12T for timer0. Set TMOD bits.
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
 * @brief Run timer0 mode0 and wait timer not finished.
 * @details Before run timer0_mode0_12T_init or timer0_mode0_1T_init   
 * should be called. 
 * After run program flow blocked until timer does not overloaded.
 * Dont mix call of timer0_mode0_run_once_and_wait with
 * timer0_mode0_start/timer0_mode0_stop calls.
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
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

//============================== Timer2 mode0 declarations end ============================

//============================== Timer0 mode0 declarations begin ==========================

void timer0_mode1_12T_init();

//============================== Timer0 mode0 declarations end ============================
#endif