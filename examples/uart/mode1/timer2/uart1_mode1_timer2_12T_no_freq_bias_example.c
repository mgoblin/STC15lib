/**
 * Show frequency bias on UART1 mode1 baudrate
 */
#include <uart1_mode1_timer2_12T.h>
#include <frequency.h>
#include <delay.h>

#define LED P10

void main()
{
    // Slow down the clock frequency two times
    set_frequency_divider_scale(2);

    uart1_mode1_timer2_12T_init(RxD_P30_TxD_P31);
    
    // Baudrate is 9600. Calling start_ext takes into account the frequency divider.
    uart1_mode1_timer2_12T_start_ext(9600);

    while (1)
    {
        LED = !LED;

        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte('\r');
        uart1_send_byte('\n');

        delay_ms(2000);
    }
}
