#include <timer0_to_ms.h>

uint32_t timer_uint16_ticks_to_freq100
(
    uint16_t ticks, 
    uint8_t timer_clock_divider,
    uint8_t frequency_divider_scale
)
{
    return (100 * get_master_clock_frequency() / ((timer_clock_divider << 1) * (1 + (uint32_t)ticks))) >> frequency_divider_scale;
}

uint16_t timer0_frequency_to_ticks_unsafe(uint32_t frequency)
{
    // TODO Corner cases for fequency parameter value
    uint8_t timer_clock_divider = get_timer0_clock_divider();
    uint16_t ticks = (get_master_clock_frequency() >> 1) / (frequency * timer_clock_divider);
    return (ticks >> get_frequency_divider_scale());
}