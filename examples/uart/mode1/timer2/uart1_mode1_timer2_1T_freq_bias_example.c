/**
 * Show frequency bias on UART1 mode1 baudrate
 */
#include <uart1_mode1_timer2_1T.h>
#include <frequency.h>
#include <delay.h>

#define LED P10

void main()
{
    // Slow down the clock frequency two times
    set_frequency_divider_scale(1);

    uart1_mode1_timer2_1T_init(RxD_P30_TxD_P31);
    
    /* 
    Baudrate is 4800
    uart1_mode1_timer2_1T_start(baudrate_9600);
    */

    uart1_mode1_timer2_1T_start_ext(9600);

    while (1)
    {
        LED = !LED;

        uart1_send_byte(' ');
        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte('\r');
        uart1_send_byte('\n');

        delay_ms(2000);
    }
}
