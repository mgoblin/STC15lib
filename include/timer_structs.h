#ifndef STC15_TIMER_STRUCTSH
#define STC15_TIMER_STRUCTSH

/**
 * @brief Timer clock divider values enum
 * 
 * @ingroup timer
 */
typedef enum 
{
    /// Sysclk/1
    T1 = 1, 
    /// Sysclk/12
    T12 = 12
} timer_clock_divider_t;

/**
 * @brief Timer clock start status enum
 * 
 * @ingroup timer
 */
typedef enum
{
    /// @brief Timer started
    OK,
    /// @brief Timer will be ticks only on INT pin is high
    ONLY_ON_INT_PIN_HIGH
} start_status_t;

#endif