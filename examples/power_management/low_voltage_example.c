/** 
* Low voltage detection example
* 
* For this example you need to connect VCC and GND to external power supply.
* And UART to PC GND, RxD, TxD pins only.
* When VCC is about 2.5-2.6V, MCU will set low voltage flag.
*/
#include <power_management.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

void main(void)
{
    uart1_init(9600);

    while (1)
    {
        printf_tiny("Low voltage flag is %x\r\n", power_low_voltage_flag_get());
        power_low_voltage_flag_clear();

        delay_ms(1000);

    }
}