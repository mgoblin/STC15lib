#include <uart1_mode1_timer2_12T_ext.h>

uint16_t uart1_mode1_timer2_12T_ticks(uint32_t baudrate)
{
    return 65536 - ((((MAIN_Fosc / 12) / baudrate) >> 2) >> get_frequency_divider_scale());
}