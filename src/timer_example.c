#include <sys.h>

#include <stdint.h>

#define LED P10

void reload_timer() 
{
    TMOD = 0x00;
    TL0 = 0x1f;
    TH0 = 0xff;
}

void run_timer()
{
    TF0 = 0;
    TR0 = 1;

    while(!TF0)
    {
    }
}

void main()
{
    LED = !LED;
    
    for(uint16_t i = 0; i < 128 * 10; i++)
    {
        reload_timer();
        run_timer();
    }
}