/**
 * How to use interrupt
 * 
 * This example blink LED using int0.
 */
#include <sys.h>
#include <delay.h>
#include <interrupt.h>

#define LED P10
#define INT1 P33

// INT0 handler
void int0_handler() __interrupt(INTERRUPT_INT1)
{
    LED = !LED; // LED on/off
}

void main()
{
    enable_mcu_interrupts();
    enable_int1_interrupt();

    while (1)
    {
        INT1 = !INT1; // raise INT0 interrupt
        delay_ms(500);
    }
    
}