#include <timer_to_ms_common.h>
#include <sys.h>

uint16_t timer_8bit_ticks_to_mcs(uint8_t ticks, timer_clock_divider_t div, uint8_t frequency_divider_scale) 
{
    uint16_t tick_12T_mcs = 12000000 / (MAIN_Fosc >> frequency_divider_scale);
    uint16_t mcs_12T = (ticks * tick_12T_mcs);
    return div == T12 ? mcs_12T : (mcs_12T / 12);
}
