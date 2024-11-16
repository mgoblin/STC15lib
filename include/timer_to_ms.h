#ifndef STC15_TIMER_To_MSH
#define STC15_TIMER_To_MSH

/**
 * @file timer_to_ms.h
 * @defgroup timer_to_ms Timer Aux
 * @details Functions and data structures for converting timer ticks to frequency and times.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>

/** @name frequency and ticks
 *  ticks to frequency and vice versa convertions  
 */
///@{

/**
 * @brief Convert ticks to PIN output meander frequency
 * @details The output frequency = (SYSclk/12)/((65536-[RL_TH0, RL_TL0]) * 2)
 * Frequency is biased by MCU clock frequency divider.
 * 
 * uint16 ticks used in mode 0, 1, 3
 * 
 * @param ticks timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer_to_ms
 */
uint32_t timer_uint16_ticks_to_freq(uint16_t ticks);

///@}

#endif