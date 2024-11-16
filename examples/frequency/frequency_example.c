#include <sys.h>
#include <frequency.h>
#include <delay.h>

#define LED P10

void main()
{
    set_frequency_divider_scaler(7); // set system clock value to master clock / 128

    while (1)
    {
        LED = !LED;
        delay_ms(500); // but delay still 500 ms because delay know about frequency divider
    }
}