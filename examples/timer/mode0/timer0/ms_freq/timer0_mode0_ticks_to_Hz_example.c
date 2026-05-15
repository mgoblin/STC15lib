/**
 * @file timer0_mode0_ticks_to_Hz_example.c
 * @brief Example demonstrating conversion from timer0 ticks to frequency (Hz) 
 * 
 * This example shows how to convert a desired number of timer ticks to the
 * corresponding frequency in Hz for Timer0 in Mode 0 (16-bit timer mode).
 * 
 * The example configures Timer0 to run in 1T mode (one clock cycle per count)
 * and enables output on P3.5 pin. It demonstrates how to calculate the
 * timer frequency from a given tick value and outputs this information
 * over UART.
 * 
 * Key components demonstrated:
 * - Timer0 initialization in Mode 0 with 1T timing
 * - Enabling timer output on P3.5 pin
 * - Converting timer ticks to frequency using timer0_mode0_ticks_to_Hz()
 * - Starting the timer with a specific number of ticks
 * - Serial communication using UART at 9600 baud
 * - Using delay functions
 * 
 * Hardware setup:
 * - LED connected to P1.0 (toggles on timer interrupt)
 * - UART connected for serial output
 * - Timer0 output on P3.5 pin (shows timer signal)
 * 
 * @note The actual frequency will depend on the system clock frequency
 *       defined in sys.h (MAIN_Fosc). With the default 11.0592MHz clock,
 *       a tick value of 0x0000 corresponds to approximately 5.53 MHz.
 * 
 * @see timer0_mode0_to_ms.h - Header containing Hz to ticks conversion functions
 * @see uart.h - Header for UART communication functions
 * @see delay.h - Header for delay functions
 * 
 */

#include <timer0_mode0_to_ms.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

/// @brief LED pin
#define LED P10

/// @brief Timer0 ticks count.  
#define TICKS 0x0000 // uint16 modify to change timer frequency

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


/// @brief  Entry point
void main()
{    
    // Initialize Timer0 in Mode 0 (16-bit timer) with 1T timing
    // In 1T mode, the timer increments once per system clock cycle
    timer0_mode0_1T_init();
    
    // Enable Timer0 output on P3.5 pin
    // This will show the timer signal on the pin (useful for debugging with oscilloscope)
    timer0_mode0_enable_P35_output();

    // Enable Timer0 interrupt
    // This will call timerISR() on timer0 overflow
    enable_timer0_interrupt();

    // Calculate the timer frequency corresponding to the specified tick value
    // The function timer0_mode0_ticks_to_Hz() converts ticks to frequency in Hz
    const uint32_t timer_frequency = timer0_mode0_ticks_to_Hz(TICKS);

    // Start Timer0 with the specified number of ticks
    // The timer will count down from this value and generate an overflow interrupt
    timer0_mode0_start(TICKS);

    // Initialize UART1 at 9600 baud rate for serial communication
    uart1_init(9600);
    
    // Main loop - continuously output the timer frequency over UART
    while (1) 
    {
       // Print the calculated timer frequency to serial monitor
       printf_fast("Timer frequency is %lu Hz\r\n", timer_frequency); 
       
       // Add a small delay between measurements
       delay_ms(100);
    }
}