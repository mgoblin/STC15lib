#include <sys.h>
#include <delay.h>
#include <timer0_mode0.h>

#include <uart.h>
#include <stdio.h>

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

void main()
{
    timer0_mode0_1T_init();

    uart1_init(9600);

    while(1)
    {
        // LED blinking during 1 second 
        timer0_mode0_start(0xffff);
        delay_ms(1000);

        // Not LED blinking during 2 seconds
        timer0_mode0_stop();
        interrupt_counter = 0;
        delay_ms(2000);

        if (test_if_bit_set(AUXR, 7))
        {
            printf_tiny("UART init does not clear AUXR.7. Its ok\n");
        }
    }
}