/**
 * Power down and wakeup timer example
 * 
 * Init wakeup timer and in cycle power down and change LED state.
 * As a result LED is blinking. Frequency of blinking is depends on WAKEUP_TIMER_TICKS value.
 * 
 * Second part of example demostrate reading wakeup timer internal frequency.
 * The frequency uint16_t value is available in RAM on 0xf8 and 0xf9 addresses
 * SDCC compiler before call main() method clear all RAM bytes. To avoid RAM clearing by 
 * SDCC compiler _mcs51_genRAMCLEAR() implemented as empty routine.
 */
#include <power_management.h>

#include <uart.h>
#include <stdio.h>

#define LED P10
#define WAKEUP_TIMER_TICKS 0x07ff

void _mcs51_genRAMCLEAR() {}

void main()
{
    uart1_init(9600);

    wakeup_timer_init(WAKEUP_TIMER_TICKS);

    while(1)
    {
        power_down();
        LED = !LED;

        uint16_t clk_freq = wakeup_timer_internal_clk_freq();
        printf_tiny("Wakeup freq %uHz\r\n", clk_freq);
    }
}
