#include <uart1_mode2.h>

#include <delay.h>

void uart1_mode2_init(uart1_pins_t pins, uart1_mode2_baudrate_t baudRate)
{
    enable_mcu_interrupts();
    enable_uart1_interrupt();

    /* PCON.7 always set to 1. Is it error? */
    baudRate == baudrate_345600 ? bit_set(PCON, SBIT7) : bit_clr(PCON, SBIT7);
    
    /* SM1 = 1, SM0 = 0 to select UART1 mode2 */
    SCON = 0x90;

    /* Set AUXR1 bits 6, 7 to select RxD/TxD pins */
    AUXR1 &= 0x3F;
    AUXR1 |= pins;
}

void main()
{
    uart1_mode2_init(RxD_P36_TxD_P37, baudrate_345600);

    while (1)
    {
        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte('\r');
        uart1_send_byte(PCON);
        uart1_send_byte('\n');

        delay_ms(1000);
    }
    
}

