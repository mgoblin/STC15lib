#include <timer2_to_ms.h>

uint16_t timer2_mode0_baudrate_to_ticks(uint32_t uart_baudrate)
{
    return (get_master_clock_frequency() >> get_frequency_divider_scale())/4/uart_baudrate;
}