/**
 * @file timer0_mode0_delay_ms_example.c
 * @brief Example demonstrating Timer0 Mode 0 blocking delay with millisecond precision
 * 
 * This example shows how to use Timer0 in Mode 0 (16-bit timer mode) with
 * millisecond-based blocking delays. It demonstrates the timer0_mode0_delay_ms()
 * function which allows specifying the delay duration directly in milliseconds
 * rather than calculating tick values manually.
 * 
 * The example configures Timer0 to run in 1T mode (one clock cycle per count)
 * and uses the blocking delay function to wait for 1 millisecond. The LED on
 * P1.0 toggles every 1000 delay iterations, resulting in a blink rate of once
 * per second (1ms * 1000 = 1000ms = 1s).
 * 
 * Key components demonstrated:
 * - Timer0 initialization in Mode 0 with 1T timing (fastest mode)
 * - Using timer0_mode0_delay_ms() for blocking millisecond delays
 * - LED blinking using precise timing delays
 * - Simple loop-based timing control
 * 
 * Hardware setup:
 * - LED connected to P1.0 (blinks every 1 second )
 * 
 * @note The timer0_mode0_delay_ms() function blocks program execution until
 *       the specified delay has elapsed. This is suitable for simple timing
 *       applications where the CPU can afford to wait.
 * 
 * @see timer0_mode0.h - Header for Timer0 Mode 0 functions
 * @see timer0_mode0_to_ms.h - Header containing millisecond-based timer functions
 * 
 */
#include <timer0_mode0.h>
#include <frequency.h>
#include <timer_ms_to_ticks_table.h>

/// LED pin connected to P1.0
#define LED P11

/// Delay duration in milliseconds
#define DELAY_MS 1

/// Number of delay iterations before toggling LED (1000 * 1ms = 1000ms = 1s)
#define DELAY_SCALE 1000

/**
 * @brief Main function for Timer0 Mode 0 blocking delay example
 * 
 * This function initializes Timer0 and enters an infinite loop where it
 * performs precise 1ms delays and toggles an LED every 1000 iterations.
 * 
 * Operation flow:
 * 1. Initialize Timer0 in Mode 0 with 1T timing (one timer count per clock cycle)
 * 2. Enter infinite loop:
 *    - Perform DELAY_SCALE (1000) iterations of 1ms blocking delays
 *    - Toggle LED on P1.0 after each 1000ms interval
 *    - Repeat indefinitely
 * 
 * @note The timer runs synchronously (blocking), meaning the CPU waits during
 *       each delay period and cannot perform other tasks
 * @note The LED blink rate is exactly 1Hz (once per second) with 1ms delays
 * @note Using 1T mode provides the highest resolution timing but consumes more
 *       power than 12T mode
 */
void main(void)
{
    set_frequency_divider_scale(7);

    // Initialize Timer0 in Mode 0 (16-bit timer) with 1T timing
    // In 1T mode, the timer increments once every system clock cycle
    timer0_mode0_1T_init();
    
    timer0_1ms_delay_init();

    // Main loop - continuously delay and toggle LED
    while (1) {
        // Perform 1000 iterations of 1ms delays (total 1000ms = 1 second)
        for(uint16_t i = 0; i < DELAY_MS * DELAY_SCALE; i++)
        {
            timer0_1ms_delay();
        }
        // Toggle LED - blink rate is 1Hz (once per second)
        LED = !LED;
    }
}
