#include <counter0_mode0.h>
#include <pin.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

#define LED P10
#define COUNTER_INIT_VALUE 65435U

void counter0_mode0_init()
{
    enable_mcu_interrupts();
    enable_timer0_interrupt();

    // TMOD.3/GATE = 0;
    // TMOD.2/(Timer or Counter mode) = 1;
    // TMOD.1/M1 timer0 = 0; 
    // TMOD.0/M0 timer0= 0;
    TMOD |= 0x04; // init Counter0

    counter0_mode0_set_value(0x00);
}

void counter0_mode0_start()
{
    TR0 = 1;
}

void counter0_mode0_set_value(uint16_t value)
{
    TH0 = (uint8_t)(value >> 8);
    TL0 = (uint8_t)(value & 0xff);
}

uint16_t counter0_mode0_get_value()
{
    return (((uint16_t) TH0) << 8) | TL0;
}

void counter0_mode0_stop()
{
    TR0 = 0;
}

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    uart1_init(9600);

    counter0_mode0_init();
    counter0_mode0_set_value(COUNTER_INIT_VALUE);
    counter0_mode0_start();
    
    pin_quasi_bidiretional_init(P3, 4);

    while (1) {
        T0 = !T0;
        delay_ms(50);
        if (!T0)
        {
            printf_tiny(
                "Tick %u\r\n", 
                counter0_mode0_get_value() - COUNTER_INIT_VALUE);
        }
    }
}