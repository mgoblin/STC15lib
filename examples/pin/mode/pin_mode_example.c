/**
 * How to test pin mode
 */
#include <pin.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

void print_pin_mode()
{
    bool is_quasi_bidiretional = is_pin_mode_quasi_bidiretional(P1, 0);
    bool is_push_pull = is_pin_mode_push_pull(P1, 0);
    bool is_input_only = is_pin_mode_input_only(P1, 0);
    bool is_open_drain = is_pin_mode_open_drain(P1, 0);
    printf_tiny("q-bi: %d, push-pull: %d, input-only: %d, open-drain: %d\n", 
        is_quasi_bidiretional, 
        is_push_pull,
        is_input_only,
        is_open_drain);
}

void f_delay_ms(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
    uart1_init(9600);
    while (1)
    {
        pin_quasi_bidiretional_init(P1, 0);
        printf_tiny("Set q-bi mode\n");
        print_pin_mode();
        f_delay_ms(200);

        pin_push_pull_init(P1, 0);
        printf_tiny("Set push-pull mode\n");
        print_pin_mode();
        f_delay_ms(200);

        pin_input_only_init(P1, 0);
        printf_tiny("Set input-only mode\n");
        print_pin_mode();
        f_delay_ms(200);

        pin_open_drain_init(P1, 0);
        printf_tiny("Set open-drain mode\n");
        print_pin_mode();
        f_delay_ms(200);

        f_delay_ms(3000);
        printf_tiny("\n");
    }
    
}