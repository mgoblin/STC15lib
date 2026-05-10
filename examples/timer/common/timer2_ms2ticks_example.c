/**
 * This example shows how to use the timer2_ms_to_ticks 
 * to calculate the number of timer 2 ticks for a given duration.
 * 
 * The duration is specified in milliseconds.
 * If the specified duration divided by the interrupt scaling factor 
 * can be serviced by the timer2 - its started and the LED is blinking.
 * 
 * Otherwise uart1 initialized and error message send through UART. 
 */

#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <uart.h>
#include <stdio.h>

// LED pin
#define LED P10

// ISR count up to this scaler
#define ISR_SCALER 10

// LED light on duration
#define DURATION_MS 500

// ISR scaler current value
uint8_t isr_scaler_value = 0;

/*
 * Timer2 interrupt request handler
 * 
 * Counts Timer2 interrupts and  flip the LED state every ISR_SCALER times.
 */
void timerISR() __interrupt(INTERRUPT_TIMER2)
{
    if (isr_scaler_value == ISR_SCALER)
    {
        LED = !LED;
        isr_scaler_value = 0;
    }
    else
    {
        isr_scaler_value++;
    }
}

void main()
{
    timer2_mode0_12T_init();
    // Calculate timer2 ticks count given duration
    // ticks_count is equals to 0 if given duration can not be serviced.
    uint16_t ticks = timer2_ms_to_ticks(DURATION_MS / ISR_SCALER);
    
    // start timer2 if it supports given duration
    if (ticks > 0) 
    { 
        timer2_mode0_start(ticks); 
    } 
    // otherwise init uart1 for sending error message
    else 
    {
        uart1_init(9600);
    }
    
    while (1) 
    {
        // If given duration not supported - send error message through UART
        if (ticks == 0)
        {
            printf_tiny("Duration %u cannot be serviced by timer2\r\n", DURATION_MS);
        }
    }
}