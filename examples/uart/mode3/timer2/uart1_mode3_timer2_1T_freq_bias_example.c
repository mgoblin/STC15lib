/**
 * Show frequency bias on UART1 mode3 baudrate
 */
#include <uart1_mode3_timer2_1T.h>
#include <frequency.h>
#include <delay.h>

#define LED P10

void main()
{
    // Slow down the clock frequency two times
    set_frequency_divider_scale(1);

    uart1_mode3_timer2_1T_init(RxD_P30_TxD_P31);
    
    /* 
    Baudrate is 4800
    uart1_mode3_timer2_1T_start(baudrate_9600);
    */

    uart1_mode3_timer2_1T_start_ext(9600);

    while (1)
    {
        LED = !LED;

        uart1_send_9bit(' ', 0);
        uart1_send_9bit('O', 1);
        uart1_send_9bit('k', 0);
        uart1_send_9bit('\r', 1);
        uart1_send_9bit('\n', 0);

        delay_ms(500);
    }
}
