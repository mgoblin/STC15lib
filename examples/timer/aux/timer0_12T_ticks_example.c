/**   
 * Demonstrtate convertions between timer ticks and frequency
 * 
 * Ticks count and frequency is approximation.
 * For 2.5 kHz tick count is 0x5C, but set 0x5C ticks get 2477.41 Hz frequency. 
 * 
 * LED lighting doing only for firmwatre diagnostic.
 */

#include <timer0_mode0.h>
#include <timer0_to_ms.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#include <stdlib.h>

#define LED P10

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    // Init timer and set timer output to P35 (pin P3.5)
    timer0_mode0_12T_init();
    timer0_mode0_enable_P35_output(true);

    // Set MCU clock divider to 2. MCU slowdown. 
    set_frequency_divider_scale(1);
    // Calculate ticks count to frequency 2.5 kHz. Value is 0x5C
    uint16_t ticks = timer0_frequency_to_ticks_unsafe(2500);
    // Store MCU clock divider to print it in while cycle
    uint8_t freq_divider = get_frequency_divider();
    // Calculate P35 meander frequency and its value is 2477.41, not 2500
    uint32_t freq = timer0_uint16_ticks_to_freq100(ticks);
    // Restore MCU clock divider. If dont restore then uart is biased from clock divider 
    // and not printing 
    set_frequency_divider_scale(0);
    
    // Start timer
    timer0_mode0_start(ticks);

    // Get string representation of timer frequency to fstr variable
    char fstr[32];
    __ultoa(freq, fstr, 10);

    uart_init(9600);
    while(1) 
    {
        delay_ms(300);
        printf_tiny("Ticks for 2500 Hz and freq_divider %u is 0x%x\n", freq_divider, ticks);
        printf_tiny("Vice versa 100 * frequency is %s\n", fstr);
    }
}