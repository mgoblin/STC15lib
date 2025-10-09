/**
 * How to send data with uart1 in mode3 with even parity bit
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

        uart1_send_byte_even_parity(' ');
        uart1_send_byte_even_parity('O');
        uart1_send_byte_even_parity('k');
        uart1_send_byte_even_parity('\r');
        uart1_send_byte_even_parity('\n');

        delay_ms(500);
    }
}
