/**
 * @file timer2_mode0_ticks_to_Hz_example.c
 * @brief Example demonstrating conversion from timer2 ticks to frequency (Hz) 
 * 
 * This example shows how to convert a desired number of timer ticks to the
 * corresponding frequency in Hz for timer2 in Mode 0 (16-bit timer mode).
 * 
 * The example configures timer2 to run in 1T mode (one clock cycle per count). 
 * It demonstrates how to calculate the timer frequency from a given tick value and outputs this information
 * over UART.
 * 
 * Key components demonstrated:
 * - timer2 initialization in Mode 0 with 1T timing
 * - Converting timer ticks to frequency using timer2_mode0_ticks_to_Hz()
 * - Starting the timer with a specific number of ticks
 * - Serial communication using UART at 9600 baud
 * - Using delay functions
 * 
 * Hardware setup:
 * - LED connected to P1.0 (toggles on timer interrupt)
 * - UART connected for serial output
 * 
 * @see timer2_mode0_to_ms.h - Header containing Hz to ticks conversion functions
 * @see uart.h - Header for UART communication functions
 * @see delay.h - Header for delay functions
 * 
 */

#include <timer2_mode0_to_ms.h>

#include <uart.h>
#include <stdio.h>

/// @brief LED pin
#define LED P10

/// @brief timer2 ticks count.  
#define TICKS 0xFFFF // uint16 modify to change timer frequency

/**
 * @brief timer2 interrupt service routine
 * 
 * This function is called when timer2 overflows. It toggles the LED
 * connected to P1.0 to provide a visual indication of timer interrupts.
 * 
 * @note The interrupt is automatically cleared by the hardware
 */
void timerISR() __interrupt(INTERRUPT_TIMER2)
{
    LED = !LED;
}


/// @brief  Entry point
void main()
{    
    // Initialize timer2 in Mode 0 (16-bit timer) with 1T timing
    // In 1T mode, the timer increments once per system clock cycle
    timer2_mode0_1T_init();
    
    // Calculate the timer frequency corresponding to the specified tick value
    // The function timer2_mode0_ticks_to_Hz() converts ticks to frequency in Hz
    const uint32_t timer_frequency = timer2_mode0_ticks_to_Hz(TICKS);

    // Start timer2 with the specified number of ticks
    // The timer will count down from this value and generate an overflow interrupt
    timer2_mode0_start(TICKS);

    // Initialize UART1 at 9600 baud rate for serial communication
    uart1_init(9600);
    
    // Main loop - continuously output the timer frequency over UART
    while (1) 
    {
       // Print the calculated timer frequency to serial monitor
       // 11059200 Hz
       printf_fast("Timer frequency is %lu Hz\r\n", timer_frequency); 
    }
}