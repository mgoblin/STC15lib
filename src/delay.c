#include <bits.h>
#include <delay.h>
#include <frequency.h>

void delay_ms(uint16_t ms)
{
    uint16_t ms_div = ms / get_frequency_divider();
    unsigned int i;
    do
    {
       i = (get_master_clock_frequency() / 13000);
       while (--i); //14T per loop
    } while (--ms_div);
}