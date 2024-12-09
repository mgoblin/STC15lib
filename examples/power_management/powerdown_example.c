#include <power_management.h>

#include <delay.h>


#define LED P10
#define OFF 1
#define ON 0

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

    wakeup_timer_init(0x0001);
    wakeup_timer_start();

    power_down();
}
