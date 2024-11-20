#include <timer2_to_ms.h>

uint16_t timer2_mode0_baudrate_to_ticks(uint32_t uart_baudrate)
{
    return 0xffff - (65536 - (MAIN_Fosc/4/uart_baudrate));
}