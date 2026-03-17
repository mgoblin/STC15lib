#include <comparator.h>

#define LED     P10

#define CMPIF   0x40    // CMPCR1.6 : Interrupt flag bit of comparator
#define CMPRES  0x01    // CMPCR1.0 : Result bit of comparator

void cmpISR(void) __interrupt(INTERRUPT_CMPR)
{
    CMPCR1 &= ~CMPIF;           //Clear the finishing flag
    LED = !!(CMPCR1 & CMPRES);  //Output the result CMPRES to test pin to display
}

void main(void)
{
    comparator_init_async();
    comparator_start();
    
    while(1);
}