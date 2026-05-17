/**
 * @file timer0_mode2_Hz_to_ticks_example.c
 * @brief Example demonstrating conversion from frequency (Hz) to timer0 ticks
 * 
 * This example shows how to convert a desired frequency in Hz to the
 * corresponding number of timer ticks for Timer0 in Mode 2 (8-bit auto-reload timer mode).
 * 
 * The example configures Timer0 to run in 1T mode (one clock cycle per count)
 * and calculates the number of ticks needed for a 500 kHz (500,000 Hz) timer
 * overflow frequency using the timer0_mode2_Hz_to_ticks() function. It then
 * starts the timer and toggles an LED on each timer overflow via interrupt.
 *
 * Key components demonstrated:
 * - Timer0 initialization in Mode 2 with 1T timing
 * - Converting frequency to timer ticks using timer0_mode2_Hz_to_ticks()
 * - Starting the timer with the calculated tick count
 * - Timer interrupt service routine toggling an LED
 * 
 * Hardware setup:
 * - LED connected to P1.0 (toggles on timer interrupt)
 * 
 * @note The actual tick value will depend on the system clock frequency
 *       defined in sys.h (MAIN_Fosc). With the default 11.0592 MHz clock
 *       and 1T timer mode, a 500 kHz overflow frequency corresponds to
 *       approximately 21 ticks. Since timer0 mode2 is 8-bit (0-255 ticks),
 *       ensure the calculated ticks fit within this range; otherwise the
 *       conversion will overflow and return 0.
 * 
 * @see timer0_mode2_to_ms.h - Header containing Hz to ticks conversion functions
 * @see frequency.h - Header for clock divider functions
 * 
 */

#include <timer0_mode2_to_ms.h>
#include <frequency.h>
#include <uart.h>
#include <stdio.h>

/// @brief LED pin
#define LED P10

/// @brief Desired timer overflow frequency in Hz
#define FREQ_HZ 500000UL

/**
 * @brief Timer0 interrupt service routine
 * 
 * This function is called when Timer0 overflows. It toggles the LED
 * connected to P1.0 to provide a visual indication of timer interrupts.
 * 
 * @note The interrupt is automatically cleared by the hardware
 */
void timerISR() __interrupt(INTERRUPT_TIMER0)
{
    LED = !LED;
}

/**
 * @brief Entry point
 */
void main(void)
{
    // Initialize Timer0 in Mode 2 with 1T timing
    timer0_mode2_1T_init();
    // Enable Timer0 interrupt
    enable_timer0_interrupt();

    // Calculate the timer ticks corresponding to the desired frequency
    const uint8_t ticks = timer0_mode2_Hz_to_ticks(FREQ_HZ);
    // Start Timer0 with the calculated ticks
    timer0_mode2_start(ticks);

    uart1_init(9600);

    // Main loop: wait for interrupts
    while (1) {
        printf_tiny("Ok\r\n");
    }
}
