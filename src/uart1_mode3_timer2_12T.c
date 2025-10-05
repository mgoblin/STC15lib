#include <uart1_mode3_timer2_12T.h>
#include <delay.h>

void uart1_mode3_timer2_12T_init(uart1_pins_t pins)
{
    enable_mcu_interrupts();
    enable_uart1_interrupt();
    disable_timer2_interrupt();

    PCON &= 0x3F;
    SCON = 0xD0;

    /* The clock source of Timer 2 is SYSclk/12. AUXR.T2x12 = 0 */  
    /* AUXR.UART_M0x6 = 0 */                                        
    /* Timer2 is not started. AUXR.T2R = 0 */                       
    /* Timer2 are used as timer. AUXR.T2_C/T = 0 */                 
    AUXR &= 0xC2;                           
                                            
    /* Select Timer2 as UART1 baud rate generator. AUXR.S1ST2 = 1; */ 
    bit_set(AUXR, SBIT0);                   
                                            
    /* Point-to-point mode */               
    bit_clr(CLK_DIV, CBIT4);                
                                            
    /* Set AUXR1 bits 6, 7 to select RxD/TxD pins */                 
    AUXR1 &= 0x3F;                          
    AUXR1 |= pins;                          
}

void uart1_mode3_timer2_12T_start(uart1_mode3_timer2_12t_baudrate_t baudrate)
{
    /* Set TH TL values */
    T2L = baudrate & 0xFF;
    T2H = baudrate >> 8;

    /* Start Timer2 */
    bit_set(AUXR, SBIT4);
}

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
        uart1_send_byte('O');
        uart1_send_byte('k');
        uart1_send_byte(SCON);
        uart1_send_byte('\r');
        uart1_send_byte('\n');

        LED = 1;
        delay_ms(500);
    }
}