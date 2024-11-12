#include <timer0_mode2.h>

#define LED P10
#define SLOW_DOWN_CYCLES 1000

uint16_t interrupt_counter = 0;

void timer0ISR(void) __interrupt(1)
{
    if (interrupt_counter++ >= SLOW_DOWN_CYCLES)
    {
        interrupt_counter = 0;
        LED = !LED;
    }
}

void main()
{
    timer0_mode2_12T_init();

    // LED blinking during 1 second 
    timer0_mode2_start(0xff);

    while(1) {}
}