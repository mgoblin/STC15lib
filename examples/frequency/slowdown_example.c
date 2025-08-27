/**
 * How to dynamically slowdown MCU frequency and not biase to delay_ms
 * 
 * Slow down MCU frequency. 
 * LED blinking is 1 sec period (0.5 sect ON and 0.5 sec OFF) on any 
 * frequency divider because delay_ms adapted to frequency divider changes.
 */
#include <frequency.h>
#include <delay.h>

#define LED P10

void main()
{
    for(uint8_t divider = 0; divider < 8; divider++)
    {
        // set system clock freq divider value to master clock to slowdown MCU
        set_frequency_divider_scale(divider); 
        
        LED = !LED;
        
        // but delay still 500 ms because delay know about frequency divider
        delay_ms(500); 
    }
}