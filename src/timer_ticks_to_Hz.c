#include <timer_to_ms_common.h>
#include <sys.h>

float timer_ticks_to_Hz(uint16_t ticks, timer_clock_divider_t timer_clock_divider, uint16_t frequency_divider_scale) 
{ 
  return (MAIN_Fosc >> frequency_divider_scale) / (float)(timer_clock_divider * (1 + ticks));
}

