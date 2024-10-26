#include <sys.h>
#include <delay.h>
#include <timer.h>

#define LED P10

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    timer0_mode0_12T_init(); // init timer0
    
    // enable output of timer to P3.5 pin. The signal is _|‾|_|‾|_
    timer0_mode0_enableP35_output(true); 

    timer0_mode0_start(0xff, 0x00); //start timer

    while (1) {}
}