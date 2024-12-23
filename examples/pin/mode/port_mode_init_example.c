/**
 * How to set pin mode for all port (P3) pins
 */

#include <pin.h>

#include <delay.h>


#define PORT P3
#define DELAY 250

void f_delay_ms(uint8_t ms)
{
    delay_ms(ms);
}

void main()
{
    while (1)
    {
        port_mode_quasi_bidiretional_init(P3);
        f_delay_ms(DELAY);

        port_mode_pull_push_init(P3);
        f_delay_ms(DELAY);

        port_mode_input_only_init(P3);
        f_delay_ms(DELAY);

        port_mode_open_drain_init(P3);
        f_delay_ms(DELAY);
    }
}