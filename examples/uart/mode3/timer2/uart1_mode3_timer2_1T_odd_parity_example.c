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

        uart1_send_byte(' ', PARITY_ODD);
        uart1_send_byte('O', PARITY_ODD);
        uart1_send_byte('k', PARITY_ODD);
        uart1_send_byte('\r', PARITY_ODD);
        uart1_send_byte('\n', PARITY_ODD);

        delay_ms(500);
    }
}
