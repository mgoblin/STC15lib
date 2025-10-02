/**
 * How to synchronous send and receive data with uart1 in mode1
 * 
 * On start uart1 will receive byte and send back "<recieved byte> Okr\r\n"
 */

#include <uart1_mode1_timer2_1T.h>

#include <delay.h>

#define LED P10

void main()
{
    uart1_mode1_timer2_1T_init(RxD_P30_TxD_P31);
    uart1_mode1_timer2_1T_start(baudrate_115200);

    while (1)
    {
        LED = !LED;

        uint8_t data;
        uart1_receive_byte(&data);
        uart1_send_byte(data);

        uart1_send_byte(' ');
        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte('\r');
        uart1_send_byte('\n');

        delay_ms(2000);
    }
}
