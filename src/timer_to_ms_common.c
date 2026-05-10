#include <timer_to_ms_common.h>
#include <sys.h>

uint16_t timer_16bit_ticks_to_ms(uint16_t ticks, timer_clock_divider_t div, uint8_t frequency_divider_scale) 
{
    uint16_t tick_12T_mcs = 12000000 / (MAIN_Fosc >> frequency_divider_scale);
    uint16_t ms_12T = (ticks * tick_12T_mcs) / 1000;
    return div == T12 ? ms_12T : (ms_12T / 12);
}

uint16_t timer_8bit_ticks_to_mcs(uint8_t ticks, timer_clock_divider_t div, uint8_t frequency_divider_scale) 
{
    uint16_t tick_12T_mcs = 12000000 / (MAIN_Fosc >> frequency_divider_scale);
    uint16_t mcs_12T = (ticks * tick_12T_mcs);
    return div == T12 ? mcs_12T : (mcs_12T / 12);
}

uint16_t timer_ms_to_ticks(uint16_t ms, timer_clock_divider_t divider, uint8_t frequency_divider_scale)
{
  uint32_t mcu_freq_ms = MAIN_FoscH >> frequency_divider_scale;
  uint32_t timer_freq_ms = mcu_freq_ms / divider;
  uint32_t ticks_count = ms * timer_freq_ms;

  return (ticks_count >= UINT16_MAX) ? 0 : (uint16_t) ticks_count;
}