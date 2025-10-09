/**
 * How to receive data with uart1 in mode3 with odd parity bit
 * 
 */

#include <uart1_mode3_timer2_12T.h>

#define LED P10

void main()
{
    uint8_t data = 0;
    
    uart1_mode3_timer2_12T_init(RxD_P30_TxD_P31);
    uart1_mode3_timer2_12T_start(baudrate_9600);

    while (1)
    {
        LED = !LED;

        uart1_receive_byte_odd_parity(data);

        uart1_send_byte_odd_parity(data);
        uart1_send_byte_odd_parity('\r');
        uart1_send_byte_odd_parity('\n');
    }
}
