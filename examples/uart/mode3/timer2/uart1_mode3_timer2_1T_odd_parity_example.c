/**
 * How to send data with uart1 in mode3 with odd parity
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

        uart1_send_byte_odd_parity(' ');
        uart1_send_byte_odd_parity('O');
        uart1_send_byte_odd_parity('k');
        uart1_send_byte_odd_parity('\r');
        uart1_send_byte_odd_parity('\n');

        delay_ms(500);
    }
}
