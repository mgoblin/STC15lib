#include <sys.h>
#include <delay.h>
#include <timer0_mode1.h>

#define LED P10

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

void delay(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
    timer0_mode1_1T_init();

    // LED blinking during 1 second 
    timer0_mode1_start(0xffff);
    delay(1000);

    // Not LED blinking during 2 seconds
    timer0_mode1_stop();
    interrupt_counter = 0;
    delay(2000);
}