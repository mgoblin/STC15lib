#include <timer_to_ms_common.h>
#include <sys.h>

uint16_t timer_ms_to_ticks(uint16_t ms, timer_clock_divider_t divider, uint8_t frequency_divider_scale)
{
  uint16_t mcu_freq_ms = MAIN_FoscH >> frequency_divider_scale;
  uint16_t timer_freq_ms = mcu_freq_ms / divider;
  uint16_t ticks_count = ms * timer_freq_ms;

  return (ticks_count >= UINT16_MAX) ? 0 : ticks_count;
}
