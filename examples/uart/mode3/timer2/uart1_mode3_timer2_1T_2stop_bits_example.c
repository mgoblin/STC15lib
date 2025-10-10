/**
 * How to synchronous send and receive data with uart1 in mode3
 * with 2 stop bits
 */

#include <uart1_mode3_timer2_1T.h>

#include <delay.h>

#define LED P10

void main()
{
    uart1_mode3_timer2_1T_init(RxD_P30_TxD_P31);
    uart1_mode3_timer2_1T_start(baudrate_115200);

    while (1)
    {
        LED = !LED;

        uart1_send_byte_2stop_bits(' ');
        uart1_send_byte_2stop_bits('O');
        uart1_send_byte_2stop_bits('k');
        uart1_send_byte_2stop_bits('\r');
        uart1_send_byte_2stop_bits('\n');

        delay_ms(500);
    }
}
