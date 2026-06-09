#include <timer0_mode0_to_ms.h>

#define LED P10

#define TIMER0_FREQ_HZ 100
#define ISR_SCALE 100

volatile uint8_t isr_counter = 0;

void timerISR() __interrupt(INTERRUPT_TIMER0)
{
    isr_counter++;
    if (isr_counter == ISR_SCALE)
    {
        LED = !LED;
        isr_counter = 0;
    }
}
void main(void)
{
    timer0_mode0_12T_init();

    timer0_mode0_start_Hz(TIMER0_FREQ_HZ << 1);

    for (;;);
}
