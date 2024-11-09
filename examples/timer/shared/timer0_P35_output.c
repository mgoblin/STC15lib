#include <sys.h>
#include <delay.h>
#include <timer.h>

#include <uart.h>
#include <stdio.h>
#include <delay.h>

#define LED P10

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    uart_init(9600);
    timer0_mode0_12T_init(); // init timer0

    bool output_enabled = is_timer0_P35_output_enabled();

    printf_tiny("P3.5 output enabled is %d\n", output_enabled);
    delay_ms(5000);
    
    // enable output of timer to P3.5 pin. The signal is _|‾|_|‾|_
    timer0_enableP35_output(true); 

    timer0_start(0xff00); //start timer

    output_enabled = is_timer0_P35_output_enabled();
    printf_tiny("P3.5 output enabled is %d\n", output_enabled);

    while (1) {}
}