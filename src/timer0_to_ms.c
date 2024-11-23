#include <timer0_to_ms.h>

uint32_t timer0_ticks_to_ms_usafe(uint16_t ticks)
{
    volatile uint32_t t1 = ((uint32_t)ticks + 1) * get_timer0_clock_divider();
    volatile uint32_t t2 = get_master_clock_frequency_high_part() >> get_frequency_divider_scale();
    volatile uint32_t r = t1/t2;

    return r;
}