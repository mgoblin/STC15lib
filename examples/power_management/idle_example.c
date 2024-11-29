/**
 * How to use idle.
 * 
 * Start timer0 that wake up from idle mode.
 * In main routine LED blink. 
 * Idle freeze main until timer0 interrupt arrived.
 * 
 * As a result LED blink not with delay 250 ms period but on timer period.  
 */
#include <power_management.h>

#include <delay.h>
#include <timer0_mode0.h>
#include <frequency.h>


#define LED P10

void timerISR() __interrupt(1)
{

}

void main()
{
    set_frequency_divider_scale(6);
    timer0_mode0_12T_init();
    timer0_mode0_start(0xffff);

    while(1)
    {
        LED = !LED;
        delay_ms(250);
        
        idle();
    }
}