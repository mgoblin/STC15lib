/**
 * @file timer0_mode2_delay_ms_example.c
 * @brief Example demonstrating Timer0 Mode 2 delay-based timing with millisecond resolution
 * 
 * This example shows how to use Timer0 in Mode 2 (8-bit auto-reload timer mode)
 * with millisecond-based delay functions. It demonstrates the timer0_mode2_delay_ms()
 * function which provides blocking delay functionality for precise timing control.
 * 
 * The example configures Timer0 to run in 12T mode (twelve clock cycles per count)
 * and uses the delay function to create precise millisecond delays. The LED connected
 * to P1.0 toggles once per second, providing a visual indication of the timing accuracy.
 * 
 * Key components demonstrated:
 * - Timer0 initialization in Mode 2 with 12T timing
 * - Using timer0_mode2_delay_ms() for blocking millisecond delays
 * - LED blinking with precise timing control
 * - Loop-based delay scaling for longer timing periods
 * 
 * 
 * Hardware setup:
 * - LED connected to P1.0 (blinks every 1 second)
 * 
 * 
 * @see timer0_mode2.h - Header for Timer0 Mode 2 functions
 * @see timer0_mode2_to_ms.h - Header containing millisecond-based timer functions
 * 
 */

#include <timer0_mode2_to_ms.h>

/// LED pin connected to P1.0
#define LED P10

/// Delay duration in milliseconds
#define DELAY_MS 1

/// Number of delay iterations before toggling LED (1000 * 1ms = 1000ms = 1s)
#define DELAY_SCALE 1000

/**
 * @brief Main function for Timer0 Mode 2 delay-based timing example
 * 
 * This function initializes Timer0 in Mode 2 with 12T timing and enters
 * an infinite loop that creates precise 1-second intervals by performing
 * 1000 iterations of 1ms delays, then toggles the LED to visualize the timing.
 * 
 * Operation flow:
 * 1. Initialize Timer0 in Mode 2 with 12T timing (one timer count per 12 clock cycles)
 * 2. Enter infinite loop performing 1ms delays
 * 3. After 1000 delays (1 second), toggle the LED
 * 4. Repeat indefinitely
 * 
 * The delay is implemented using a busy-wait loop with timer0_mode2_delay_ms()
 * which configures Timer0 for the specified duration and waits for completion.
 * During the delay, the CPU is blocked and cannot perform other tasks.
 * 
 * @note The timer runs synchronously during delay, blocking CPU execution
 * @note LED blink rate is 1Hz (once per second) with 50% duty cycle
 * @note For non-blocking timing, consider using timer interrupts instead
 */
void main(void)
{
    timer0_mode2_12T_init();

    // Main loop - continuously delay and toggle LED
    while (1) {
        // Perform 1000 iterations of 1ms delays (total 1000ms = 1 second)
        for(uint16_t i = 0; i < DELAY_SCALE; i++)
        {
            timer0_mode2_delay_ms(DELAY_MS);
        }
        // Toggle LED - blink rate is 1Hz (once per second)
        LED = !LED;
    }
}
