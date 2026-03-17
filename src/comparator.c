#include <interrupt.h>
#include <delay.h>
#include <comparator.h>

#define LED     P10

#define CMPIF   0x40    // CMPCR1.6 : Interrupt flag bit of comparator
#define CMPRES  0x01    // CMPCR1.0 : Result bit of comparator

#define PIS     0x08    // CMPCR1.3 : bit to choose the postive pole of comparator
#define NIS     0x04    // CMPCR1.2 : bit to choose the negative pole of comparator

#define CMPOE   0x02    // CMPCR1.1 : bit to enable the comparator output to test pin

#define INVCMPO 0x80    // CMPCR2.7 : bit to invert the comparator output
#define DISFLT  0x40    // CMPCR2.6 : bit to disable the comparator filter

#define LCDTY   0x3F    // CMPCR2.[5:0] : set the Duty of Level-Change control filter in the output terminal of comparator

#define PIE     0x20    // CMPCR1.5 : Pos-edge Interrupt Enabling bit
#define NIE     0x10    // CMPCR1.4 : Neg-edge Interrupt Enabling bit

#define CMPEN   0x80    // CMPCR1.7 : Enable bit of comparator

void cmpISR(void) __interrupt(INTERRUPT_CMPR)
{
    CMPCR1 &= ~CMPIF;           //Clear the finishing flag
    LED = !!(CMPCR1 & CMPRES);  //Output the result CMPRES to test pin to display
}

void main(void)
{
    CMPCR1 = 0; //Initilize the Comparator control register 1
    CMPCR2 = 0; //Initilize the Comparator control register 2

    CMPCR1 &= ~PIS; //choose external pin P5.5(CMP+) as the postive pole of comparator
    CMPCR1 &= ~NIS; //choose internal BandGap Votage BGV as the negative pole of comparator

    CMPCR1 &= ~CMPOE; // Forbid the comparator output to test pin
    CMPCR2 &= ~INVCMPO; //Normal output the comparing result of comparator on P1.2

    CMPCR2 &= ~DISFLT; // Enable the comparator filter
    CMPCR2 &= ~LCDTY;

    CMPCR1 |= PIE; // Enable Pos-edge Interrupt
    CMPCR1 |= NIE; // Enable Neg-edge Interrupt

    CMPCR1 |= CMPEN; //Enable Comparator

    enable_mcu_interrupts();
    
    while(1);
}