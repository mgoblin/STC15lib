#include <power_management.h>

#define LED P10
#define LED_ON_SECONDS 3

void main(void)
{
    wakeup_timer_init_seconds(LED_ON_SECONDS);
    
    while (1)
    {
        power_down();
        LED = !LED;
    }
}