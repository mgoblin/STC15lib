#include <sys.h>
#include <frequency.h>
#include <uart.h>
#include <stdio.h>
#include <delay.h>

#define LED P10

void print_master_clock_output()
{
    switch (get_master_clock_output_pin())
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

void main()
{
    uart_init(9600);
    
    enable_master_clock_output_div4();
    set_master_clock_output_pin(P5_4);
    print_master_clock_output();
    delay_ms(100);

    disable_master_clock_output();
    print_master_clock_output();
    delay_ms(100);

    enable_master_clock_output_div4();
    set_master_clock_output_pin(P1_6);
    print_master_clock_output();
    delay_ms(100);

}