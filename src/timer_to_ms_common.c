#include <timer_to_ms_common.h>

uint16_t timer_ms_to_ticks(uint16_t ms, timer_clock_divider_t timer_clock_divider)
{
    return ms * ((get_master_clock_frequency_high_part() + 26) >> get_frequency_divider_scale()) / timer_clock_divider;
}