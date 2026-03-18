#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define LED P10

void main(void)
{
    while (1)
    {
        LED = !LED;
    }
}