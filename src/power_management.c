#include <power_management.h>

#define WIRC_H_ADDRESS 0xf8
#define WIRC_L_ADDRESS 0xf9

uint16_t wakeup_timer_internal_clk_freq()
{
    volatile __idata uint8_t * const wirc_h_ptr = (__idata uint8_t *) WIRC_H_ADDRESS;
    volatile __idata uint8_t * const wirc_l_ptr = (__idata uint8_t *) WIRC_L_ADDRESS;
    return ((uint16_t)*wirc_h_ptr << 8) | *wirc_l_ptr;
}
