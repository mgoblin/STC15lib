#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10
#define BLINKS 3

uint8_t interrupt_counter = 0;

void timer0ISR(void) __interrupt(1)
{
    interrupt_counter++;
    if (interrupt_counter == 12)
    {
        interrupt_counter = 0;
        LED = !LED;
    }
}

void main()
{
    timer0_mode0_1T_init();

    timer0_mode0_start(0x00, 0x00);

    delay_ms(2000);

    timer0_mode0_stop();

    delay_ms(2000);
}