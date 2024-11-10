#ifndef STC15_TIMER_STRUCTSH
#define STC15_TIMER_STRUCTSH

/**
 * Timer clock divider
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
 * @brief timer reload status
 * 
 * @details In some modes timers tick can be reloaded without restarting 
 * 
 * @ingroup timer
 */
typedef enum
{
    /// @brief ticks reloaded
    OK = 0,
    /// @brief timer doesnt started yet and ticks not reloaded. You sould start timer before
    NOT_STARTED = 1,
    /// @brief timer ticks reloading doesnt supported in this timer/mode 
    NOT_SUPPORTED_IN_MODE = 2
} reload_status_t;

#endif