/**
 * @file timer0_mode0_start_ms_example.c
 * @brief Example demonstrating Timer0 Mode 0 operation with millisecond-based timing
 * 
 * This example shows how to use Timer0 in Mode 0 (16-bit timer mode) with
 * millisecond-based configuration. It demonstrates the timer0_mode0_start_ms()
 * function which allows specifying the timer duration directly in milliseconds
 * rather than calculating tick values manually.
 * 
 * The example configures Timer0 to run in 12T mode (twelve clock cycles per count)
 * and starts the timer with a 50ms overflow period. Each time the timer overflows,
 * an interrupt service routine increments a counter, and every 10th overflow
 * toggles an LED connected to P1.0, resulting in an LED blink rate of once
 * per 500ms (50ms * 10).
 * 
 * Key components demonstrated:
 * - Timer0 initialization in Mode 0 with 12T timing
 * - Starting Timer0 with millisecond duration using timer0_mode0_start_ms()
 * - Timer interrupt service routine for periodic actions
 * - LED blinking using timer interrupts
 * - Serial output of timer tick values
 * 
 * Hardware setup:
 * - LED connected to P1.0 (blinks every 500ms)
 * - UART1 connected for serial communication (9600 baud)
 * 
 * @note The timer duration in milliseconds is converted internally to the
 *       corresponding number of ticks based on the system clock frequency
 *       defined in sys.h (MAIN_Fosc) and the timer mode (12T in this case).
 *       With the default 11.0592MHz clock and 12T mode, 50ms corresponds
 *       to approximately 45,875 ticks.
 * 
 * @see timer0_mode0.h - Header for Timer0 Mode 0 functions
 * @see timer0_mode0_to_ms.h - Header containing millisecond-based timer functions
 * 
 */

#include <timer0_mode0_to_ms.h>

#include <uart.h>
#include <stdio.h>

/// LED pin connected to P1.0
#define LED P10

/// Timer overflow duration in milliseconds
#define TIMER_DURATION_MS 50

/// Scale factor for LED blinking (blink every 10th timer overflow)
#define LED_BLINK_SCALE 10

/// Counter for timer interrupts, incremented on each overflow
volatile uint8_t isr_count = 0;

/**
 * @brief Timer0 interrupt service routine
 * 
 * This function is called each time Timer0 overflows. It maintains a counter
 * of timer overflows and toggles the LED every LED_BLINK_SCALE overflows,
 * providing a visual indication of the timer's operation.
 * 
 * The interrupt service routine:
 * - Increments the isr_count counter on each timer overflow
 * - Toggles the LED on P1.0 every 10th overflow (500ms interval)
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
 * @brief Main function for Timer0 Mode 0 millisecond timing example
 * 
 * This function initializes the timer and UART, configures Timer0 to overflow
 * every TIMER_DURATION_MS milliseconds, and enters an infinite loop while
 * the timer operates in the background using interrupts.
 * 
 * Operation flow:
 * 1. Initialize UART1 at 9600 baud rate for serial communication
 * 2. Configure Timer0 in Mode 0 with 12T timing (one timer count per 12 clock cycles)
 * 3. Calculate and start Timer0 with the specified millisecond duration
 * 4. Continuously output the calculated tick count via UART
 * 5. Timer overflow interrupts toggle the LED without CPU intervention
 * 
 * @note The timer runs asynchronously in the background, allowing the main
 *       loop to perform other tasks while maintaining precise timing
 * @note The printf_tiny function is used for efficient serial output
 */
void main(void)
{
    uart1_init(9600);

    // Initialize Timer0 in Mode 0 (16-bit timer) with 12T timing
    // In 12T mode, the timer increments once every 12 system clock cycles
    timer0_mode0_12T_init();

    // Calculate the number of ticks corresponding to the desired millisecond duration
    // This value is calculated based on the system clock frequency and 12T mode
    uint16_t ticks = timer0_mode0_ms_to_ticks(TIMER_DURATION_MS);
    
    // Start Timer0 with the specified millisecond duration
    // The timer will overflow approximately every TIMER_DURATION_MS milliseconds
    timer0_mode0_start_ms(TIMER_DURATION_MS);

    // Main loop - continuously output the tick value over UART
    while (1) {
        printf_tiny("Ticks = %u\r\n", ticks);
    }
}
