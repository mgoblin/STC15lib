#include <timer0_to_ms.h>

uint32_t timer0_ticks_to_ms_usafe(uint16_t ticks)
{
    uint32_t t2 = get_master_clock_frequency_high_part() >> get_frequency_divider_scale();
    uint32_t t1 = (uint32_t)ticks + 1;
    return (get_timer0_clock_divider() == T12 ? (12 * t1) : t1) / t2;
}