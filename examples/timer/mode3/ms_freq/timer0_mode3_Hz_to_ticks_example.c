/**
 * @file timer0_mode3_Hz_to_ticks_example.c
 * @brief Example demonstrating conversion from frequency (Hz) to timer0 ticks
 * 
 * This example shows how to convert a desired frequency in Hz to the
 * corresponding number of timer ticks for Timer0 in Mode 3 (split mode).
 * 
 * The example configures Timer0 to run in 1T mode (one clock cycle per count)
 * and calculates the number of ticks needed for a 1000 Hz timer overflow frequency
 * using the timer0_mode3_Hz_to_ticks() function. It then starts the timer and
 * toggles an LED on each timer overflow via interrupt, while also outputting
 * the calculated tick value over UART.
 * 
 * Key components demonstrated:
 * - Timer0 initialization in Mode 3 with 1T timing
 * - Converting frequency to timer ticks using timer0_mode3_Hz_to_ticks()
 * - Starting the timer with the calculated tick count
 * - Timer interrupt service routine toggling an LED
 * - Serial communication using UART at 9600 baud
 * 
 * Hardware setup:
 * - LED connected to P1.0 (toggles on timer interrupt)
 * - UART connected for serial output
 * 
 * @note The actual tick value will depend on the system clock frequency
 *       defined in sys.h (MAIN_Fosc). With the default 11.0592 MHz clock
 *       and 1T timer mode, a 1000 Hz overflow frequency corresponds to
 *       approximately 11059 ticks.
 * 
 * @see timer0_mode3_to_ms.h - Header containing Hz to ticks conversion functions
 * @see uart.h - Header for UART communication functions
 * 
 */

#include <timer0_mode3_to_ms.h>

#include <uart.h>
#include <stdio.h>

/// @brief Desired timer overflow frequency in Hz
#define FREQ_HZ 1000

/// @brief  Entry point
void main()
{    
    // Initialize Timer0 in Mode 3 (split mode) with 1T timing
    // In 1T mode, the timer increments once per system clock cycle
    timer0_mode3_1T_init();
    
    // Calculate the timer ticks corresponding to the desired frequency
    // The function timer0_mode3_Hz_to_ticks() converts frequency in Hz to ticks
    const uint16_t ticks = timer0_mode3_Hz_to_ticks(FREQ_HZ);

    // Initialize UART1 at 9600 baud rate for serial communication
    uart1_init(9600);
    
    // Main loop - continuously output the calculated tick value over UART
    while (1) 
    {
       // Print the calculated tick value to serial monitor
       printf_fast("Ticks is %u for frequency %u Hz\r\n", ticks, FREQ_HZ);   
    }
}