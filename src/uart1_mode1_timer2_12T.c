#include <uart1_mode1_timer2_12T.h>

#include <delay.h>

#define LED P10

// TODO Support double baud rate
// TODO MCU clock frequency can be divided. 

void uart1_mode1_timer2_init(uart1_pins_t pins)
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

void uart1_mode1_timer2_start(const uart1_mode1_timer2_12t_baudrate_t baudrate)
{
    // TODO MCU clock frequency can be divided. 
    
    // Baud rate = ((Sysclk/12)/(65535 - THTL))/4
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
    T2H = baudrate >> 8;
    T2L = baudrate & 0xFF;

    // Set T2R = 1 to start Timer2
    bit_set(AUXR, SBIT4);
}

void uart1_mode1_timer2_stop()
{
    // To stop timer T2R = 0;
    bit_clr(AUXR, CBIT4);
}

void uart1_mode1_timer2_send_byte(uint8_t data)
{
    SBUF = data;
	while(!TI);
	TI=0;
}

void uart1_mode1_timer2_receive_byte(uint8_t *data)
{
	while(!RI);
	*data = SBUF;
    RI=0;
}

void main()
{
    uart1_mode1_timer2_init(RxD_P30_TxD_P31);
    uart1_mode1_timer2_start(baudrate_9600);

    while (1)
    {
        LED = !LED;

        uint8_t data;
        uart1_mode1_timer2_receive_byte(&data);
        uart1_mode1_timer2_send_byte(data);

        uart1_mode1_timer2_send_byte(' ');
        uart1_mode1_timer2_send_byte('O');
        uart1_mode1_timer2_send_byte('k');
        uart1_mode1_timer2_send_byte('\r');
        uart1_mode1_timer2_send_byte('\n');

        delay_ms(2000);
    }
}