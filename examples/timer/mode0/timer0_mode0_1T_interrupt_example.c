#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10
#define BLINKS 3

uint8_t interrupt_counter = 0; // interrupt counter. 

void timer0ISR(void) __interrupt(1)
{
    // Every 12th interrupt call switch LED state and reset counter
    if (interrupt_counter++ == 12)
    {
        interrupt_counter = 0;
        LED = !LED;
    }
}

void main()
{
    timer0_mode0_1T_init();

    // LED blinking during 1 second 
    timer0_mode0_start(0x00, 0x00);
    delay_ms(1000);

    // Not LED blinking during 2 seconds
    timer0_mode0_stop();
    interrupt_counter = 0;
    delay_ms(2000);
}