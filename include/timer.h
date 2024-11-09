#ifndef STC15_TIMERH
#define STC15_TIMERH

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

#include <timer0.h>
#include <timer2.h>


#endif