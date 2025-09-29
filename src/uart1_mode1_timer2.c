#include <uart1_mode1_timer2.h>

#include <uart.h>
#include <stdio.h>
#include <delay.h>

#define LED P10
void uart1_mode1_timer2_init()
{
    enable_mcu_interrupts();
    enable_uart1_interrupt();

    PCON &= 0x3F;
    SCON = 0x50;
    
    // TODO choose RxD TxD pins
    
    // The clock source of Timer 2 is SYSclk/12. T2x12 = 0
    
    // TODO Maybe we can use 1T mode to get better baud rate?

    // No double baud rate. UART_M0x6 = 0
    // Timer2 not started. T2R
    // Timer2 used as timer. T2_C/T = 0
    AUXR &= 0xC2; 

    // Select Timer2 as UART1 baud rate generator. S1ST2 = 1;
    bit_set(AUXR, SBIT0);

    disable_timer2_interrupt();

    // Select UART1 normal mode (not relay and broadcast mode)
    bit_clr(CLK_DIV, CBIT4);
}

void uart1_mode1_timer2_start(const uint32_t baudrate)
{
    // TODO MCU clock frequency can be divided. 
    
    // TODO Baud rate = ((Sysclk/12)/(65535 - THTL))/4
    // 4 * baudrate = (Sysclk/12)/(65535 - THTL)
    // (4 * baudrate) * (65535 - THTL) = Sysclk/12
    // 65535 - THTL = (Sysclk/12)/(4 * baudrate)
    // THTL = 65535 - (Sysclk/12)/(4 * baudrate)
    //
    // Baud rate = 9600, Sysclk = 11059200
    //
    // THTL = 65535 - (11059200/12)/(4 * 9600)
    // THTL = 65535 - 921600/38400
    // THTL = 65535 - 24 = 65511 = 0xFFE7
    T2H = 0xFF;
    T2L = 0xE7;

    // To start Timer2 T2R = 1;
    bit_set(AUXR, SBIT4);
}

void uart1_mode1_timer2_stop()
{
    // To stop timer T2R = 0;
    // Befrore stopping the timer, we need waiting for the last byte to be sent
}

void main()
{
    uart1_mode1_timer2_init();
    uart1_mode1_timer2_start(9600);

    while (1)
    {
        LED = !LED;

        printf_tiny("Ok\r\n");

        delay_ms(2000);
    }
}