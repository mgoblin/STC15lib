#include <sys/sys.h>
#include <frequency/frequency.h>
#include <uart/uart.h>

#include <stdio.h>

void main()
{
    uart_init(9600);

    printf_tiny("CPU freq is %d", get_cpu_frequency_high_part());
    printf_tiny("%d Hz\n", get_cpu_frequency_low_part());
}