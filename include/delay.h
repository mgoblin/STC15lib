#ifndef STC15_DELAYH
#define STC15_DELAYH

/**
 * @file delay.h
 * @defgroup delays Delay
 * @details Functions and data structures related to delaying program flow
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <frequency.h>

#define TICKS_DELAY_1ms ((uint16_t) (((get_master_clock_frequency() / 1000UL) - 30UL) / 18UL))

/** 
*  @brief Delays program flow using CPU nop
*  @details Using CPU cycles to delay. Use delay_ms with care. 
*
*  @param ms uint16_t delay value
*  
*  @ingroup delays 
*/
void delay_ms(uint16_t ms);

#endif