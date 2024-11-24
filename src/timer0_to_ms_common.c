#include <timer_to_ms_common.h>

uint32_t timer_ticks_to_ms_usafe(uint16_t ticks, timer_clock_divider_t timer_divider, uint8_t frequency_divider_scale)
{
    return ((1UL + (uint32_t)ticks) / ((get_master_clock_frequency_high_part() / timer_divider) >> frequency_divider_scale) >> 1);
}
