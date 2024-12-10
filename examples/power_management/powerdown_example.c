#include <power_management.h>

#include <delay.h>


#define LED P10
#define OFF 1
#define ON 0

/** Dont clear memory */
void _mcs51_genRAMCLEAR() {}


void delay(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
   delay(250);
   LED = ON;
    
   delay(250);
   LED = OFF;

    wakeup_timer_init(0xffff);
    wakeup_timer_start();

    power_down();
}
