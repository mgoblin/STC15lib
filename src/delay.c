#include <bits.h>
#include <delay.h>
#include <frequency.h>

void delay_ms(uint16_t ms)
{
    //uint8_t cpu_freq_divider = 1 << and_mask(CLK_DIV, 0b00000111);
    //uint16_t ms_div = ms / cpu_freq_divider;
    unsigned int i;
    do
    {
       i = (get_master_clock_frequency() / 13000);
       while (--i); //14T per loop
    } while (--ms);
}