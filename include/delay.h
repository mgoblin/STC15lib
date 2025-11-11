#ifndef STC15_DELAYH
#define STC15_DELAYH

/**
 * @file delay.h
 * @defgroup delays Delay
 * @details Functions and data structures related to delaying program flow
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <frequency.h>

/**
 * @brief Ticks for 1ms delay
 * 
 * @ingroup delays 
 */
#define TICKS_DELAY_1MS()               \
do {                                    \
	volatile uint8_t i, j;              \
	i = 5;	                            \
	j = 79;                             \
	do                                  \
	{                                   \
		while (--j);                    \
	} while (--i);                      \
} while(0)

/** 
*  @brief Delays program flow using CPU nop
*  @details Using CPU cycles to delay. Use delay_ms with care. 
*
*  @param ms uint16_t delay value
*  
*  @ingroup delays 
*/
#define delay_ms(ms)                                            \
do {                                                            \
	volatile uint16_t ms_div = ms >> get_frequency_divider_scale();     \
    do {															\
		TICKS_DELAY_1MS();                                    	\
	} while(--ms_div);											\
} while(0)                                                      \

#endif