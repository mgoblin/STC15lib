#include <sys.h>
#include <delay.h>
#include <interrupts.h>

#define LED P10
#define INT0 P32

// INT0 handler
void int0_handler() __interrupt(0)
{
    LED = !LED; // LED on/off
}

void main()
{
    enable_mcu_interrupts();
    enable_int0_interrupt();

    while (1)
    {
        INT0 = !INT0; // raise INT0 interrupt
        delay_ms(500);
    }
    
}