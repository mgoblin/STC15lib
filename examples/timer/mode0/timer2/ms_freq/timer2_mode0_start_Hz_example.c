/**
 * @file timer2_mode0_start_Hz_example.c
 * @brief Example demonstrating Timer2 Mode 0 operation with frequency-based timing
 * 
 * This example shows how to use Timer2 in Mode 0 (16-bit timer mode) with
 * frequency-based configuration. It demonstrates the timer2_mode0_start_Hz()
 * function which allows specifying the timer overflow frequency directly in
 * Hertz rather than calculating tick values manually.
 * 
 * The example configures Timer2 to run in 12T mode (twelve clock cycles per count)
 * and starts the timer with a 200Hz overflow frequency (since the example uses
 * TIMER2_FREQ_HZ >> 1 = 200Hz). Each time the timer overflows, an interrupt
 * service routine increments a counter, and every 100th overflow toggles an
 * LED connected to P1.0, resulting in an LED blink rate of once per second
 * (200Hz / 100 = 2Hz LED toggle = 1 blink per second).
 * 
 * Key components demonstrated:
 * - Timer2 initialization in Mode 0 with 12T timing
 * - Starting Timer2 with frequency in Hertz using timer2_mode0_start_Hz()
 * - Timer interrupt service routine for periodic LED blinking
 * - Frequency-based timer configuration
 * 
 * Hardware setup:
 * - LED connected to P1.0 (blinks once per second)
 * 
 * @note The actual timer frequency in Hz is specified as TIMER2_FREQ_HZ << 1
 *       (left-shifted by 1), which effectively doubles the base frequency.
 *       With the default 11.0592MHz system clock and 12T timer mode, the
 *       timer calculates the appropriate tick count to achieve the desired
 *       overflow frequency.
 * 
 * @see timer2_mode0.h - Header for Timer2 Mode 0 functions
 * @see timer2_mode0_to_ms.h - Header containing frequency-based timer functions
 * @see timer2_mode0_Hz_to_ticks - Function for manual Hz to ticks conversion
 * 
 */

#include <timer2_mode0_to_ms.h>

/// @brief LED pin connected to P1.0
#define LED P10

/// @brief Base timer overflow frequency in Hz (doubled before use)
#define TIMER2_FREQ_HZ 100

/// @brief Scale factor for LED blinking (blink every 100th timer overflow)
#define ISR_SCALE 100

/// @brief Counter for timer interrupts, incremented on each overflow
volatile uint8_t isr_counter = 0;

/**
 * @brief Timer2 interrupt service routine
 * 
 * This function is called each time Timer2 overflows. It maintains a counter
 * of timer overflows and toggles the LED every ISR_SCALE overflows, providing
 * a visual indication of the timer's operation.
 * 
 * The interrupt service routine:
 * - Increments the isr_counter on each timer overflow
 * - Toggles the LED on P1.0 every 100th overflow
 * - Automatically clears the interrupt flag (hardware handled)
 * 
 * @note The interrupt is automatically cleared by the hardware
 * @note The isr_counter variable must be declared volatile to prevent compiler optimization
 */
void timerISR() __interrupt(INTERRUPT_TIMER2)
{
    isr_counter++;
    if (isr_counter == ISR_SCALE)
    {
        LED = !LED;
        isr_counter = 0;
    }
}

/**
 * @brief Main function for Timer2 Mode 0 frequency-based timing example
 * 
 * This function initializes the timer and configures Timer2 to overflow
 * at the specified frequency (TIMER2_FREQ_HZ << 1 = 200Hz). The timer operates
 * asynchronously in the background using interrupts, allowing the main loop
 * to remain idle while maintaining precise timing.
 * 
 * Operation flow:
 * 1. Initialize Timer2 in Mode 0 with 12T timing (one timer count per 12 clock cycles)
 * 2. Calculate and start Timer2 with the specified frequency in Hertz
 * 3. Timer overflow interrupts toggle the LED at 1Hz (200Hz / 100)
 * 4. Main loop enters infinite wait state
 * 
 * @note The timer runs asynchronously in the background, allowing the main
 *       loop to perform other tasks while maintaining precise timing
 * @note The timer frequency is specified as TIMER2_FREQ_HZ << 1, which
 *       doubles the base frequency to 200Hz for a 1Hz LED blink rate
 */
void main(void)
{
    // Initialize Timer2 in Mode 0 (16-bit timer) with 12T timing
    // In 12T mode, the timer increments once every 12 system clock cycles
    timer2_mode0_12T_init();

    // Start Timer2 with the specified frequency in Hertz
    // The frequency is doubled using left shift: TIMER2_FREQ_HZ << 1 = 200Hz
    timer2_mode0_start_Hz(TIMER2_FREQ_HZ << 1);

    // Main loop - enter infinite wait state while timer operates in background
    for (;;);
}
