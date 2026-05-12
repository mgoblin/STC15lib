#include <timer_to_ms_common.h>
#include <sys.h>

uint8_t timer_Hz_to_ticks_8bit(uint32_t frequency, timer_clock_divider_t timer_clock_divider, uint8_t frequency_divider_scale)
{
  uint32_t timer_clk = (MAIN_Fosc >> frequency_divider_scale) / timer_clock_divider;
  uint32_t result = timer_clk / frequency;
  return (result > UINT8_MAX) ? 0 : result;
}

