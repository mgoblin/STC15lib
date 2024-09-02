#include <sys.h>
#include <delay.h>

#define LED P10

void main()
{
    LED = 1;
    delay_ms(500);
    LED = 0;
    delay_ms(500);
}