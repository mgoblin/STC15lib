/**
 * @file timer0_mode0_Hz_to_ticks_example.c
 * @brief Example demonstrating conversion from frequency (Hz) to timer0 ticks
 * 
 * This example shows how to convert a desired frequency in Hz to the
 * corresponding number of timer ticks for Timer0 in Mode 0 (16-bit timer mode).
 * 
 * The example configures Timer0 to run in 12T mode (twelve clock cycles per count)
 * and sets the MCU clock divider scale to 7 (division by 128). It calculates the
 * number of ticks needed for a 1 Hz timer overflow frequency using the
 * timer0_mode0_Hz_to_ticks() function. It then starts the timer and toggles an LED
 * on each timer overflow via interrupt.
 * 
 * Key components demonstrated:
 * - Setting MCU clock divider scale
 * - Timer0 initialization in Mode 0 with 12T timing
 * - Converting frequency to timer ticks using timer0_mode0_Hz_to_ticks()
 * - Starting the timer with the calculated tick count
 * - Timer interrupt service routine toggling an LED
 * 
 * Hardware setup:
 * - LED connected to P1.0 (toggles on timer interrupt)
 * 
 * @note The actual tick value will depend on the system clock frequency
 *       defined in sys.h (MAIN_Fosc) and the clock divider settings.
 *       With the default 11.0592 MHz clock, divider scale 7, and 12T timer mode,
 *       a 1 Hz overflow frequency corresponds to approximately 7199 ticks.
 * 
 * @see timer0_mode0_to_ms.h - Header containing Hz to ticks conversion functions
 * @see frequency.h - Header for clock divider functions
 * 
 */

#include <timer0_mode0_to_ms.h>

#include <uart.h>
#include <stdio.h>

/// @brief LED pin
#define LED P10

/// @brief Desired timer overflow frequency in Hz
#define FREQ_KHZ 1

/// @brief kHz scale
#define KHZ_SCALE 1000

/// @brief counts isr for toggling LED each 100th timer0 overflow 
volatile uint16_t isr_counter = 0;

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
    if (isr_counter++ == KHZ_SCALE)
    {
        LED = !LED;
        isr_counter = 0;
    }
}

/**
 * @brief Entry point
 */
void main(void)
{
    // Initialize Timer0 in Mode 0 with 12T timing
    timer0_mode0_12T_init();

    // Calculate the timer ticks corresponding to the desired frequency
    const uint16_t ticks = timer0_mode0_Hz_to_ticks(KHZ_SCALE * FREQ_KHZ);
    // Start Timer0 with the calculated ticks
    timer0_mode0_start(ticks);


    uart1_init(9600);
    // Main loop: wait for interrupts
    while (1) {
        printf_tiny("Ticks count is %u\r\n", ticks);
    }
}