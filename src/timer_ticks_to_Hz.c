#include <timer_to_ms_common.h>
#include <sys.h>

uint32_t timer_ticks_to_Hz(uint16_t ticks, timer_clock_divider_t timer_clock_divider, uint16_t frequency_divider_scale) 
{ 
  uint32_t cnt = (MAIN_Fosc >> frequency_divider_scale) / timer_clock_divider;
  uint32_t t = 1UL + ticks;
  return cnt / t;
}

