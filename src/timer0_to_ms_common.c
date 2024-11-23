#include <timer_to_ms_common.h>

uint32_t timer_ticks_to_ms_usafe(uint16_t ticks, timer_clock_divider_t timer_divider, uint8_t frequency_divider_scale)
{
    uint32_t t2 = get_master_clock_frequency_high_part() >> frequency_divider_scale;
    uint32_t t1 = (uint32_t)ticks + 1;
    return (timer_divider == T12 ? (12 * t1) : t1) / t2;
}
