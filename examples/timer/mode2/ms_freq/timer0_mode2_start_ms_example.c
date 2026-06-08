/**
 * @file timer0_mode2_start_ms_example.c
 * @brief Example demonstrating Timer0 Mode 2 operation with millisecond-based timing
 * 
 * This example shows how to use Timer0 in Mode 2 (8-bit timer mode) with
 * millisecond-based configuration. It demonstrates the timer0_mode2_start_ms()
 * function which allows specifying the timer duration directly in milliseconds
 * rather than calculating tick values manually.
 * 
 * The example configures Timer0 to run in 1T mode (twelve clock cycles per count)
 * and starts the timer with a 5ms overflow period. Each time the timer overflows,
 * an interrupt service routine increments a counter, and every 10th overflow
 * toggles an LED connected to P1.0, resulting in an LED blink rate of once
 * per 500ms (5ms * 100).
 * 
 * Key components demonstrated:
 * - Timer0 initialization in Mode 2 with 1T timing
 * - Starting Timer0 with millisecond duration using timer0_mode2_start_ms()
 * - Timer interrupt service routine for periodic actions
 * - LED blinking using timer interrupts
 * 
 * 
 * Hardware setup:
 * - LED connected to P1.0 (blinks every 500ms)
 * 
 * 
 * @see timer0_mode2.h - Header for Timer0 Mode 0 functions
 * @see timer0_mode2_to_ms.h - Header containing millisecond-based timer functions
 * 
 */

#include <timer0_mode2_to_ms.h>

/// LED pin connected to P1.0
#define LED P10

/// Timer overflow duration in milliseconds
#define TIMER_DURATION_MS 1

/// Scale factor for LED blinking (blink every 10th timer overflow)
#define LED_BLINK_SCALE 1000

/// Counter for timer interrupts, incremented on each overflow
volatile uint16_t isr_count = 0;

/**
 * @brief Timer0 interrupt service routine
 * 
 * This function is called each time Timer0 overflows. It maintains a counter
 * of timer overflows and toggles the LED every LED_BLINK_SCALE overflows,
 * providing a visual indication of the timer's operation.
 * 
 * The interrupt service routine:
 * - Increments the isr_count counter on each timer overflow
 * - Toggles the LED on P1.0 every 100th overflow (500ms interval)
 * - Automatically clears the interrupt flag (hardware handled)
 * 
 * @note The interrupt is automatically cleared by the hardware
 * @note The isr_count variable must be declared volatile to prevent compiler optimization
 */
void timerISR() __interrupt(INTERRUPT_TIMER0)
{
    isr_count++;
    if (isr_count == LED_BLINK_SCALE) 
    {
        LED = !LED;
        isr_count = 0;
    }
}

/**
 * @brief Main function for Timer0 Mode 2 millisecond timing example
 * 
 * This function initializes the timer, configures Timer0 to overflow
 * every TIMER_DURATION_MS milliseconds, and enters an infinite loop while
 * the timer operates in the background using interrupts.
 * 
 * Operation flow:
 * 1. Configure Timer0 in Mode 2 with 1T timing (one timer count per 1 clock cycles)
 * 2. Calculate and start Timer0 with the specified millisecond duration
 * 3. Timer overflow interrupts toggle the LED without CPU intervention
 * 
 * @note The timer runs asynchronously in the background, allowing the main
 *       loop to perform other tasks while maintaining precise timing
 */
void main(void)
{
    set_frequency_divider_scale(7);

    // Initialize Timer0 in Mode 2 (8-bit timer) with 1T timing
    // In 1T mode, the timer increments once every 1 system clock cycles
    timer0_mode2_1T_init();

    // Start Timer0 with the specified millisecond duration
    // The timer will overflow approximately every TIMER_DURATION_MS milliseconds
    timer0_mode2_start_ms(TIMER_DURATION_MS);

    // Main loop
    while (1) {}
}
