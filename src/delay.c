#include <delay/delay.h>

#define CYCLE MAIN_Fosc / 13000

void delay_ms(unsigned short ms)
{
    unsigned int i;
    do
    {
       i = MAIN_Fosc / 13000;
       while (--i); //14T per loop
    } while (--ms);
}