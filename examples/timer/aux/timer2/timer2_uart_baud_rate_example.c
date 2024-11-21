/**
 * How to use timer2 as baudrate generator for UART1
 */

#include <uart.h>
#include <stdio.h>

#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <delay.h>

#define UART_BAUDRATE 74880

uint16_t ticks_count(uint32_t baudrate)
{
    return timer2_mode0_baudrate_to_ticks(baudrate);
}

void main()
{
    // UART1 on init use timer2_mode0_baudrate_to_ticks. 
    // For high UART baudrates timer2_mode0_baudrate_to_ticks has calc deviation.
    // The reason of deviation is division inaccuracy inside timer2_mode0_baudrate_to_ticks   
    // The result of baudrates timer2_mode0_baudrate_to_ticks not exact value 
    // but good approximation.
    uart1_init(UART_BAUDRATE);
    
    // For baudrate 74880 timer2_mode0_baudrate_to_ticks result is 0x23
    // Calculation by hand get value 0x24 
    uint16_t loaded_ticks = 0x24; 
    timer2_mode0_reload(loaded_ticks); // reload ticks value of timer2 iwth more correct value

    while (1)
    {
        printf_tiny("Calulated timer2 ticks value is 0x%x\n", timer2_mode0_baudrate_to_ticks(UART_BAUDRATE));
        printf_tiny("Loaded to timer2 ticks value is 0x%x\n", loaded_ticks);
        delay_ms(500);
    }
    
}