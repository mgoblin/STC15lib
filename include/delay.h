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
#define delay_ms(ms)                                                \
{                                                                   \
    {                                                               \
        uint16_t ms_div = ms >> get_frequency_divider_scale();      \
        do                                                          \
        {                                                           \
            uint16_t d = TICKS_DELAY_1ms;                           \
            do                                                      \
            {                                                       \
                __asm NOP __endasm;                                 \
                __asm NOP __endasm;                                 \
                __asm NOP __endasm;                                 \
            } while (d--);                                          \
        } while (ms_div--);                                         \
    }                                                               \
}

#endif