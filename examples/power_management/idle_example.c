/**
 * How to use idle.
 * 
 * Start timer0 that change is_idle_required flag.
 * In main routine LED blink and idle if is_idle_required = true. 
 * Idle freeze main until timer0 interrupt arrived.
 * 
 * As a result LED blink some period of time and pause blinking until timer interrupt.  
 */
#include <power_management.h>

#include <delay.h>
#include <timer0_mode0.h>
#include <frequency.h>


#define LED P10
#define OFF 1

static bool is_idle_required = false;

void timerISR() __interrupt(1)
{
    is_idle_required = !is_idle_required;
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
        if (is_idle_required)
        {
            LED = OFF;
            idle();
        }
    }
}