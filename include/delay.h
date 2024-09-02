#ifndef STC15_DELAYH
#define STC15_DELAYH

/**
 * @file delay.h
 * @defgroup delays Delays
 * @details Functions and data structures related to delaying program flow
 * @author Michael Golovanov
 */
#include<sys.h>
#include <stdint.h>

/** 
*  @brief Delays program flow using CPU nop
*  @details Using NOP CPU cycles to delay. Use delay_ms with care. 
*
*  @param ms delay value
*  
*  @ingroup delays 
*/
void delay_ms(uint16_t ms);

#endif