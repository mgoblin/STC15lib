This C-library contains the code for interaction with STC15W408AS. STC15W408AS is a micro chip compatible with 8051 architecture.

# Versions history
0.1.0 
* first version
* system sfr headers support
* bits manipulations
* uart support

0.2.0
* headers flat structure
* doxygen documentation
* add get chip id function (value F51FC47E1D0B52 for STC15W408AS)
* add master clock and divider frequency functions
* adapt delay_ms to clock divider, uart not adapted yet

0.3.0
* add master clock output to pin P5.4 or P1.6 with dividers 1, 2, 4
* timer0 mode0 12T and 1T support implementation
* timer2 as general purpose timer with mode0 12T and 1T support implementation

