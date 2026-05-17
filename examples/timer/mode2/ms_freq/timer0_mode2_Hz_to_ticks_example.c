/**
 * @file timer0_mode2_Hz_to_ticks_example.c
 * @brief Example demonstrating conversion from frequency (Hz) to timer0 ticks
 *
 * This example shows how to convert a desired frequency in Hz to the
 * corresponding number of timer ticks for Timer0 in Mode 2 (8-bit auto-reload timer mode).
 *
 * The example calculates the number of ticks needed for a 500 kHz (500,000 Hz) timer
 * overflow frequency using the timer0_mode2_Hz_to_ticks() function and prints
 * the result via UART.
 *
 * Key components demonstrated:
 * - Timer0 initialization in Mode 2 with 1T timing
 * - Converting frequency to timer ticks using timer0_mode2_Hz_to_ticks()
 * - UART communication to display results
 *
 * @note The actual tick value will depend on the system clock frequency
 *       defined in sys.h (MAIN_Fosc). With the default 11.0592 MHz clock
 *       and 1T timer mode, a 500 kHz overflow frequency corresponds to
 *       approximately 22 ticks. Since timer0 mode2 is 8-bit (0-255 ticks),
 *       ensure the calculated ticks fit within this range; otherwise the
 *       conversion will overflow and return 0.
 *
 * @see timer0_mode2_to_ms.h - Header containing Hz to ticks conversion functions
 * @see uart.h - Header for UART communication functions
 *
 */

#include <timer0_mode2_to_ms.h>
#include <uart.h>
#include <stdio.h>

/// @brief Desired timer overflow frequency in Hz
#define FREQ_HZ 500000UL

/**
 * @brief Entry point
 */
void main(void)
{
    // Initialize Timer0 in Mode 2 with 1T timing
    timer0_mode2_1T_init();

    // Calculate the timer ticks corresponding to the desired frequency
    const uint8_t ticks = timer0_mode2_Hz_to_ticks(FREQ_HZ);

    uart1_init(9600);

    // Main loop: print ticks value repeatedly
    while (1) {
        printf_fast(
            "Ticks is %u for frequency %lu \r\n",
            ticks,
            FREQ_HZ
        );
    }
}
