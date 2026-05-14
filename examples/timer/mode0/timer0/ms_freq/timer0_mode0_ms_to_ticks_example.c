/**
 * @file timer0_mode0_ms_to_ticks_example.c
 * @brief Example demonstrating conversion from milliseconds to timer0 ticks
 * 
 * This example shows how to convert a time duration in milliseconds to the
 * corresponding number of timer ticks for Timer0 in Mode 0 (16-bit timer mode).
 * 
 * The example configures Timer0 to run in 1T mode0 (one clock cycle per count)
 * and calculates the number of ticks needed for a 3ms delay using the
 * timer0_mode0_ms_to_ticks() function. It then starts the timer and outputs the
 * calculated tick value over UART.
 * 
 * @note The actual tick value will depend on the system clock frequency
 *       defined in sys.h (MAIN_Fosc). With the default 11.0592MHz clock,
 *       3ms corresponds to approximately 33,177 ticks.
 * 
 * @see timer0_mode0.h - Header for Timer0 Mode 0 functions
 * @see timer0_mode0_to_ms.h - Header containing ms to ticks conversion functions
 * 
 */

#include <timer0_mode0_to_ms.h>

#include <uart.h>
#include <stdio.h>

/// Timer0 overflow given duration
#define DURATION_MS 3

/**
 * @brief Main function for timer0_ms2ticks_example
 */
void main()
{
    // Initialize Timer0 in Mode 0 (16-bit timer) with 1T timing
    // In 1T mode, the timer increments once per system clock cycle
    timer0_mode0_1T_init();
    
    // Enable Timer0 output on P3.5 pin
    // This will show the timer signal on the pin (useful for debugging with oscilloscope)
    timer0_mode0_enable_P35_output();

    // Convert 3 milliseconds to the corresponding number of timer ticks
    // This calculation takes into account the system clock frequency and timer mode
    uint16_t ticks = timer0_mode0_ms_to_ticks(DURATION_MS);
    
    // Start Timer0 with the calculated number of ticks
    // The timer will count down from this value and generate an overflow interrupt
    timer0_mode0_start(ticks);   
    
    // Initialize UART1 at 9600 baud rate for serial communication
    uart1_init(9600);
    
    // Main loop - continuously output the tick value over UART
    while (1) 
    {
        // Print the calculated tick value to serial monitor
        // This demonstrates the ms-to-ticks conversion result
        printf_tiny(
            "Ticks is %u for duration %u ms\r\n", 
            ticks,
            DURATION_MS
        ); // ticks = 33177
    }
}