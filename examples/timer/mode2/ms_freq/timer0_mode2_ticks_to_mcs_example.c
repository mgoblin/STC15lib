/** 
 * @file timer0_mode2_ticks_to_mcs_example.c
 * Example: Convert timer ticks to microseconds for Timer0 in Mode 2 (8-bit timer)
 *
 * This example demonstrates how to calculate the duration in microseconds
 * corresponding to a given number of timer ticks for Timer0 operating in Mode 2
 * (8‑bit timer with 1T clock). 
 *
 * Key steps:
 * 1. Set the MCU clock divider (frequency scale) to 1 (division by 2).
 * 2. Initialize UART for serial output.
 * 3. Configure Timer0 in Mode 2 with 1T clock, disable its interrupt, and
 * 4. Start the timer with a predefined tick count (0xFF, the maximum for 8‑bit).
 * 5. Convert the tick count to microseconds using the library function.
 * 6. Continuously print the result over UART.
 *
 * The conversion relies on the current system clock frequency and the timer’s
 * prescaler setting. The result is approximate due to integer arithmetic.
 */

#include <timer0_mode2_to_ms.h>

#include <uart.h>
#include <stdio.h>

/** 
 * Number of timer ticks to load into Timer0.
 * 0xFF is the maximum value for a 8‑bit timer (actually 0x1FFF),
 * but the library handles the masking internally.
 */
#define TICKS 0xff

/// @brief  entry point
void main()
{
   // Set the MCU clock divider to 1 (division by 2).
   // This ensures the timer runs at the full system clock speed.
   set_frequency_divider_scale(1);

   // Initialize UART1 at 9600 baud for serial output.
   uart1_init(9600);

   // Configure Timer0 in Mode 0 with 1T clock (no prescaler).
   timer0_mode2_1T_init();
   // Disable Timer0 interrupt (not needed for this example).
   disable_timer0_interrupt();
   // Enable timer output on pin P3.5 (square wave generation).
   timer0_mode2_enable_P35_output();
   
   // Start Timer0 with the defined tick count.
   // The timer will repeatedly count from 0 to 65535,
   // generating a periodic signal on P3.5.
   timer0_mode2_start(TICKS);

   // Convert the tick count to microseconds.
   // The function uses the current system clock and timer configuration
   // to compute the equivalent time in microseconds.
   // This routine must be called after timer0_mode0_1T_init()
   uint32_t mcs = timer0_mode2_ticks_to_mcs(TICKS);

   // Infinite loop: print the calculated high‑time every iteration.
   while (1) {
        // The printed value corresponds to the high‑time of the square wave
        // on P3.5. For a 50% duty cycle, the period is twice this value.
        printf_fast("P3.5 time is %lu mcs\r\n", mcs); // Expected output: 5 ms
   }
}