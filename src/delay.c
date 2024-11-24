#include <delay.h>

void delay_ms(uint16_t ms)
{
    {
        uint16_t ms_div = ms >> get_frequency_divider_scale();
        do
        {
            uint16_t d = TICKS_DELAY_1ms;
            do
            {
                __asm NOP __endasm;
                __asm NOP __endasm;
                __asm NOP __endasm;
            } while (d--);
        } while (ms_div--);
    }
}
