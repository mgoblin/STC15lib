#include <timer_to_ms_common.h>
#include <sys.h>

uint16_t timer_16bit_ticks_to_ms(uint16_t ticks, timer_clock_divider_t div, uint8_t frequency_divider_scale) 
{
    uint16_t tick_12T_mcs = 12000000 / (MAIN_Fosc >> frequency_divider_scale);
    uint16_t ms_12T = (ticks * tick_12T_mcs) / 1000;
    return div == T12 ? ms_12T : (ms_12T / 12);
}
uint8_t timer_frequency_to_ticks_8bit(uint32_t frequency, timer_clock_divider_t timer_clock_divider, uint8_t frequency_divider_scale)
{
  uint32_t timer_clk = (MAIN_Fosc >> frequency_divider_scale) / timer_clock_divider;
  uint32_t result = timer_clk / frequency;
  return (result > UINT8_MAX) ? 0 : result;
}


