/**
 * How to synchronous send and receive data with uart1 in mode3
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

        uart1_send_9bit(' ', 0);
        uart1_send_9bit('O', 1);
        uart1_send_9bit('k', 1);
        uart1_send_9bit('\r', 0);
        uart1_send_9bit('\n', 0);

        delay_ms(500);
    }
}
