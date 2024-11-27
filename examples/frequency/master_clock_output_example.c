/** How to output master clock signal to P5.4 / P1.6 pins */

#include <sys.h>
#include <frequency.h>
#include <uart.h>
#include <stdio.h>
#include <delay.h>

#define LED P10

// functions forward declaration
void _delay_ms_(uint16_t ms); // wrap delay_ms macro to reduce firmware size
void print_master_clock_output_pin(); // print selected master clock output pin to UART1

void main()
{
    uart1_init(9600);

    while (1)
    {
        enable_master_clock_output_div4();
        set_master_clock_output_pin(P5_4);
        print_master_clock_output_pin();
        _delay_ms_(100);

        disable_master_clock_output();
        print_master_clock_output_pin();
        _delay_ms_(100);

        enable_master_clock_output_div4();
        set_master_clock_output_pin(P1_6);
        print_master_clock_output_pin();
        _delay_ms_(100);
        
        LED = !LED; // only for see that firmware is alive
    }
}

void _delay_ms_(uint16_t ms)
{
    delay_ms(ms);
}

void print_master_clock_output()
{
    master_clock_output_pin_t pin = get_master_clock_output_pin();
    switch (pin)
    {
        case P5_4:
            printf_tiny("Master clock output pin 5.4\n");
            break;

        case P1_6:
            printf_tiny("Master clock output pin 1.6\n");
            break;    
        
        default:
            printf_tiny("Master clock output pin disabled\n");
            break;
    }    
}

