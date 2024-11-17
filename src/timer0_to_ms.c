#include <timer0_to_ms.h>

uint16_t timer0_frequency_to_ticks_unsafe(uint32_t frequency)
{
    // TODO Corner cases for fequency parameter value
    uint8_t timer_clock_divider = get_timer0_clock_divider();
    uint16_t ticks = (get_master_clock_frequency() >> 1) / (frequency * timer_clock_divider);
    return (ticks >> get_frequency_divider_scale());
}