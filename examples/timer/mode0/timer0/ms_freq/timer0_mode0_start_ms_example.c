#include <timer0_mode0_to_ms.h>

#include <uart.h>
#include <stdio.h>

#define LED P10
#define TIMER_DURATION_MS 50
#define LED_BLINK_SCALE 10

uint8_t isr_count = 0;
void timerISR() __interrupt(INTERRUPT_TIMER0)
{
    isr_count++;
    if (isr_count == LED_BLINK_SCALE) 
    {
        LED = !LED;
        isr_count = 0;
    }
}
void main(void)
{
    uart1_init(9600);

    timer0_mode0_12T_init();

    uint16_t ticks = timer0_mode0_ms_to_ticks(TIMER_DURATION_MS);
    timer0_mode0_start_ms(TIMER_DURATION_MS);

    while (1) {
        printf_tiny("Ticks = %u\r\n", ticks);
    }
}
