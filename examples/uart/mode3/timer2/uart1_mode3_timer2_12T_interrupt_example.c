#include <uart1_mode3_timer2_12T.h>

#include <delay.h>
#include <interrupt.h>

#define LED P10

void uart1_ISTR() __interrupt(4)
{
    LED = 0;
}

void main()
{
    uart1_mode3_timer2_12T_init(RxD_P30_TxD_P31);
    uart1_mode3_timer2_12T_start(baudrate_9600);

    while (1)
    {
        uart1_send_9bit('O', 1);
        uart1_send_9bit('k', 1);
        uart1_send_9bit('\r', 1);
        uart1_send_9bit('\n', 1);

        // LED off
        LED = 1;

        delay_ms(500);
    }
}
