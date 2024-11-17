#ifndef STC15_TIMER_STRUCTSH
#define STC15_TIMER_STRUCTSH

/**
 * @brief Timer clock divider values enum
 * 
 * @ingroup timer_common
 */
typedef enum 
{
    /// Sysclk/1
    T1 = 1, 
    /// Sysclk/12
    T12 = 12
} timer_clock_divider_t;

#endif