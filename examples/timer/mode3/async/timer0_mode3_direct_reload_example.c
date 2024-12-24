/**
 * Demostrate reloading timer0 on the fly.
 * ticks array contains timer ticks series that cyclic rotates 
 * with timer0_reload call after timer start.
 */
#include <timer0_mode3.h>
#include <delay.h>

#define LED P10

#define TICKS_ARRAY_SIZE 3
const uint8_t TH0_values[TICKS_ARRAY_SIZE] = {0x00, 0x80, 0xD0};
const uint8_t TL0_values[TICKS_ARRAY_SIZE] = {0x00, 0x00, 0x00};

static 
void main()
{
    set_frequency_divider_scale(3);

    timer0_mode3_12T_init();
    timer0_mode3_start(0xffff);

    while (1)
    {
        for(uint8_t idx = 0; idx < TICKS_ARRAY_SIZE; idx++)
        {
            timer0_mode3_direct_reload(TH0_values[idx], TL0_values[idx]);
            delay_ms(3000);
        }
    }
}

void timerISR() __interrupt(1)
{
    LED = !LED;
}