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
* get mode functions for timer0 and timer2
* get clock divider functions for timer0 and timer2
* timer0 mode0/12T and mode0/1T implementation with sync and interrupt (async) support. No GATE and INT0 support for timer0 running, only TR0 used for start and stop timer . No P3.5 output.  
* timer2 mode0/12T and mode0/1T implementation with interrupt (async) support. No P3.0 output.

0.4.0
* Enable and disable timer0 mode0 output to P3.5 pin supported now
* Enable and disable timer2 mode0 output to P3.0 pin supported now
* timer0_enable_on_pinINT0_high implemented for timer0 work only on INT0/P3.0 pin is high
* timer0 and timer2 use interrupts module routines
* Interrupts module implemented (with interrupts priority and int0/int1 trigger config support)

0.4.1
* frequency module use defines instead of function decl for output hex code decreasing 
* interrupts module use defines instead of function decl for firmware size decreasing
* timer module use defines on commons functionality instead of function decl for firmware size decreasing

0.5.0
* delay module now use defines instead of func decls
* all timer0 routines use define instead of function declaration 
* timer0_modeX_run_once_and_wait now have only one parameter uint_16 - timer ticks count
* timer0_start and timer2_mode0_start now have only one parameter uint_16 - timer ticks count
* TODO Timer0 mode0 reload timer routines implemented
* timer0 mode1 imeplemented

Next releases todo
* TODO timer module use defines in all functionality
* Delay module capabiltiy to use defines or func decl
* TODO Timer aux - set timers in terms of output signal freq and timings
* TODO Timers aux should not biased from CPU frequency dividers
* TODO Timers mode 2,3 should be implemented and documented 
* TODO Counters

