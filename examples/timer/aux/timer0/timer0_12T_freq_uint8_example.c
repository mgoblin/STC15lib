/** 
 * How to calculate meander frequency on P35 pin 
 * on timer0 mode2 (8-bit autoreloadable timer)
 */
#include <timer0_mode2.h>
#include <timer0_to_ms.h>

#define LED P10

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{    
    // set mcu sysclk frequency divider scaler to 2-x slowdown
    set_frequency_divider_scale(1); 
    
    // Init, configure and start timer0 in mode2
    timer0_mode2_12T_init();
    timer0_mode2_enable_P35_output(true);

    // Calculate P35 signal frequency * 100 for 0xff ticks count.
    // 0xff is a maximum value for ticks count in timer mode2. 
    // Return value is 90000 -> P35 frequency is 900 Hz. 
    uint32_t timer_frequency = timer0_uint16_ticks_to_freq100(0x00ff);

    timer0_mode2_start(0xff);

    while(1) {}
}