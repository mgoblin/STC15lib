#include <stdio.h>

#include<sys/sys.h>
#include <delay/delay.h>
#include<uart/uart.h>

void main()
{
    uart_init(9600);

    uart_send_byte(10);
    putchar('H');
    printf("ello %s", "anonymous");
}