#include <uart1_mode3_timer2_12T.h>
#include <delay.h>

void uart1_mode3_timer2_12T_init(uart1_pins_t pins)
{

}

void uart1_mode3_timer2_12T_start(uart1_mode3_timer2_12t_baudrate_t baudrate)
{

}

void uart1_mode3_timer2_12T_start_ext(uart1_mode3_timer2_12t_baudrate_t baudrate)
{

}

#define LED P10

void uart1_ISTR() __interrupt(4)
{
    if (is_uart1_send_byte_complete())
    {
        LED = 0;
    }
}

void main()
{
    uart1_mode3_timer2_12T_init(RxD_P30_TxD_P31);
    uart1_mode3_timer2_12T_start(baudrate_9600);

    while (1)
    {
        LED = 1;
        delay_ms(500);

        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte('\r');
        uart1_send_byte('\n');

        LED = 0;

        delay_ms(500);
    }
}