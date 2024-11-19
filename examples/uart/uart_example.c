#include <stdio.h>

#include<sys.h>
#include <delay.h>
#include<uart.h>

void main()
{
    uart1_init(9600);

    uart_send_byte(10);
    putchar('H');
    printf("ello %s", "anonymous");
}