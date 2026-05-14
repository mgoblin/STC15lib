/** 
 * @file timer0_mode1_ticks_to_ms_example.c
 * Example: Convert timer ticks to milliseconds for Timer0 in Mode 1 (16-bit timer)
 *
 * This example demonstrates how to calculate the duration in milliseconds
 * corresponding to a given number of timer ticks for Timer0 operating in Mode 1
 * (16‑bit timer with 1T clock). The timer is configured to output a square wave
 * on pin P3.5, and the example prints the calculated high‑time in milliseconds.
 *
 * Key steps:
 * 1. Set the MCU clock divider (frequency scale) to 1 (division by 2).
 * 2. Initialize UART for serial output.
 * 3. Configure Timer0 in Mode 1 with 1T clock, disable its interrupt, and
 *    enable the timer output on P3.5.
 * 4. Start the timer with a predefined tick count (0xFFFF, the maximum for 13‑bit).
 * 5. Convert the tick count to milliseconds using the library function.
 * 6. Continuously print the result over UART.
 *
 * The conversion relies on the current system clock frequency and the timer’s
 * prescaler setting. The result is approximate due to integer arithmetic.
 */

#include <timer0_mode1_to_ms.h>

#include <uart.h>
#include <stdio.h>

/** 
 * Number of timer ticks to load into Timer0.
 * 0xFFFF is the maximum value for a 16‑bit timer (actually 0x1FFF),
 * but the library handles the masking internally.
 */
#define TICKS 0xffff

/// @brief  entry point
void main()
{
   // Set the MCU clock divider to 1 (division by 2).
   // This ensures the timer runs at the full system clock speed.
   set_frequency_divider_scale(1);

   // Initialize UART1 at 9600 baud for serial output.
   uart1_init(9600);

   // Configure Timer0 in Mode 0 with 1T clock (no prescaler).
   timer0_mode1_1T_init();
   // Disable Timer0 interrupt (not needed for this example).
   disable_timer0_interrupt();
   
   // Start Timer0 with the defined tick count.
   // The timer will repeatedly count from 0 to 65535,
   timer0_mode1_start(TICKS);

   // Convert the tick count to milliseconds.
   // The function uses the current system clock and timer configuration
   // to compute the equivalent time in milliseconds.
   // This routine must be called after timer0_mode1_1T_init()
   uint32_t ms = timer0_mode1_ticks_to_ms(TICKS);

   // Infinite loop: print the calculated duration.
   while (1) {
        printf_fast("Timer duration is %lu ms\r\n", ms); // Expected output: 5 ms
   }
}