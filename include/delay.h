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

static uint16_t ms_div;
static unsigned int i;

/** 
*  @brief Delays program flow using CPU nop
*  @details Using NOP CPU cycles to delay. Use delay_ms with care. 
*
*  @param ms uint16_t delay value
*  
*  @ingroup delays 
*/
#define delay_ms(ms) {                              \
    ms_div = ms / get_frequency_divider_scale();    \
    do                                              \
    {                                               \
       i = (get_master_clock_frequency() / 13000);  \
       while (--i);                                 \
    } while (--ms_div);                             \
}

#endif