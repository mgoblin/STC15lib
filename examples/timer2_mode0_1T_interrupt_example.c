#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10

uint8_t interrupt_counter = 0;

void timer2ISR() __interrupt(12)
{
    interrupt_counter++;
    if (interrupt_counter == 2)
    {
        interrupt_counter = 0;
        LED = !LED;
    }
}

void main(void)
{
    timer2_mode0_1T_init();

    timer2_mode0_start(0x00, 0x00);

    delay_ms(2000);

    timer2_mode0_stop();

    delay_ms(2000);
}