#include <timer2_mode0.h>

#define LED P10
#define SLOW_DOWN_COUNT 120

uint8_t interrupt_counter = SLOW_DOWN_COUNT;

void timer2ISR() __interrupt(12)
{
    if (interrupt_counter-- <= 0)
    {
        interrupt_counter = SLOW_DOWN_COUNT;
        LED = !LED;
    }
}

void main(void)
{
    timer2_mode0_1T_init();

    timer2_mode0_start(0xffff);

    while(1) {}

}