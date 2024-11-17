#include <timer0_to_ms.h>

#define LED P10
#define TICKS 0x0000U

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{    
    timer0_mode0_1T_init();
    timer0_mode0_enable_P35_output(true);

    // For ticks = 0xffff calc result is 84.37 Hz, measurament is 84.517 Hz
    // For ticks = 0x0000 calc result is 5.529600 MHz, measurament is 5.538 MHz
    uint32_t timer_frequency = timer0_uint16_ticks_to_freq100(TICKS);

    timer0_mode0_start(TICKS);

    while (1) {}
}