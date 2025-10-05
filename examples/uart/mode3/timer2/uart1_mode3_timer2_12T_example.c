/**
 * How to send data with uart1 in mode3
 * 
 */

#include <uart1_mode3_timer2_12T.h>

#include <delay.h>

#define LED P10

void main()
{
    uart1_mode3_timer2_12T_init(RxD_P30_TxD_P31);
    uart1_mode3_timer2_12T_start(baudrate_9600);

    while (1)
    {
        LED = !LED;

        uart1_send_byte(' ');
        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte('\r');
        uart1_send_byte('\n');

        delay_ms(500);
    }
}
