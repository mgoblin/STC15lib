#include <stdio.h>

#include<sys.h>
#include <delay.h>
#include<uart.h>

void main()
{
    uart1_init(9600);

    while (1)
    {
        uart1_send_byte(10);
        putchar('H');
        printf_tiny("ello %s", "anonymous");
    }
}