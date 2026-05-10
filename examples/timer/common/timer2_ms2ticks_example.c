#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <uart.h>
#include <stdio.h>

#define LED P10
#define ISR_SCALER 10
#define DURATION_MS 50

uint8_t isr_scaler_value = 0;

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
    uint16_t ticks = timer2_ms_to_ticks(DURATION_MS);
    
    if (ticks > 0) { timer2_mode0_start(ticks); }
    
    while (1) 
    {
        if (ticks == 0)
        {
            uart1_init(9600);
            printf_tiny("Duration %u cannot be serviced by timer2\r\n", DURATION_MS);
        }
    }
}