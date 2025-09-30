#include <uart1_mode1_timer2_12T.h>

#include <delay.h>

#define LED P10

void uart1_mode1_timer2_12T_init(uart1_pins_t pins)
{
    PCON &= 0x3F;
    SCON = 0x50;
    
    // The clock source of Timer 2 is SYSclk/12. AUXR.T2x12 = 0
    // No double baud rate. AUXR.UART_M0x6 = 0
    // Timer2 is not started. AUXR.T2R = 0
    // Timer2 are used as timer. AUXR.T2_C/T = 0
    AUXR &= 0xC2; 

    // Select Timer2 as UART1 baud rate generator. AUXR.S1ST2 = 1;
    bit_set(AUXR, SBIT0);

    disable_timer2_interrupt();

    // Select UART1 normal mode (not relay and broadcast mode)
    bit_clr(CLK_DIV, CBIT4);

    // Set AUXR1 bits 6, 7 to select RxD/TxD pins
    AUXR1 &= 0x3F;
    AUXR1 |= pins; 
}

void uart1_mode1_timer2_12T_start(const uart1_mode1_timer2_12t_baudrate_t baudrate)
{
    T2H = baudrate >> 8;
    T2L = baudrate & 0xFF;

    // Set T2R = 1 to start Timer2
    bit_set(AUXR, SBIT4);
}

void uart1_mode1_timer2_12T_stop()
{
    // To stop timer T2R = 0;
    bit_clr(AUXR, CBIT4);
}

void uart1_mode1_timer2_12T_send_byte(uint8_t data)
{
    SBUF = data;
	while(!TI);
	TI=0;
}

void uart1_mode1_timer2_12T_receive_byte(uint8_t *data)
{
	while(!RI);
	*data = SBUF;
    RI=0;
}