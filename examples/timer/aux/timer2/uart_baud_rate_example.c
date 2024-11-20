/**
 * How to use timer2 as baudrate generator for UART1
 */

#include <uart.h>
#include <stdio.h>

#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <delay.h>

#define UART_BAUDRATE 74880

void main()
{
    // UART1 on init use timer2_mode0_baudrate_to_ticks. 
    // For high UART baudrates timer2_mode0_baudrate_to_ticks has calc deviation.
    // The reason of deviation is division inaccuracy inside timer2_mode0_baudrate_to_ticks   
    // The result of baudrates timer2_mode0_baudrate_to_ticks not exact value 
    // but approximation.
    uint16_t ticks = uart1_init(UART_BAUDRATE); // ticks is 0x0B for baudrate 250000
    
    // On UART_BAUDRATE 250000 ticks value 0x0B leads to ustable UART1 transmittion.
    // Decrease ticks from calulated value 0x0B to 0x0A and UART1 transmittion 
    // becomes stable.
    // For baudrate 74880 timer2_mode0_baudrate_to_ticks result is 0x23
    // Calculation with float support in PC get value 36,9 -> 37 -> 0x25 
    uint16_t loaded_ticks = 0x25; 
    timer2_mode0_reload(loaded_ticks); // reload ticks value of timer2 iwth more correct value

    while (1)
    {
        printf_tiny("Calulated timer2 ticks value is 0x%x\n", ticks);
        printf_tiny("Loaded to timer2 ticks value is 0x%x\n", loaded_ticks);
        delay_ms(500);
    }
    
}