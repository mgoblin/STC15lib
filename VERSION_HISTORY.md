# Version history
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
* timer modules now use defines instead of func decl 
* timer0_modeX_run_once_and_wait now have only one parameter uint_16 - timer ticks count
* timer0_start and timer2_mode0_start now have only one parameter uint_16 - timer ticks count
* timer0 and timer2 are modules now
* timer0 and timer2 mode0 reload timer routines implemented
* timer0 mode1 implemented
* timer2 mode0 implemented

0.6
* timer0 mode 0,1,2,3 module full implementation
* timer2 mode0 module full implementation
* Aux module convert ticks to frequency implemented 
* Aux module unsafe convert frequency to ticks
* timer_all.h to timer_common.h renamed
* delay_ms partially rewrited to asm to decrease size 
* UART to UART1 renamed
* Fix: UART bias timer0 1T by setting AUXR.7 value to 1.
* timer2 baud rate ticks calculation implemented
* UART1 use timer2_mode0 and timer2 aux modules routines now
* Implement ticks to times part of aux module for timer0, timer2 

0.7
* Fix: remove variables from delay module
* Reset routine implemented
* Watchdog timer routines implemented
* delay_ms now is define again
* Idle power managment routine implemented
* Power down mode implemented with initial wakeup timer support
* Use bitmask as a constant in bits.h to avoid unnessary bit operations in bit_set and bit_clr
* Use bitmask as a constant in bits.h to avoid unnessary bit operations in test_if_bit_set and test_if_bit_cleared

0.8
* Add memory dump example
* WakeUp timer implemented
* Times to ticks part of aux module implemented
* Docs are included to platformio package
* Examples compilation is a step of build
* Enhanced description of project for indexing in google/yandex and so on search engines
* Pin module implemented

0.9
* Pin module set port mode routines implemented
* Fix examples/mode0/timer2 compilation
* Fix timer0_mode2_reload - TH0 value should be set, now used TL0
* Fix INT0 should be defined in timer0 modes
* timerX_modeX_direct_{reload, start}(TxH, TxL) for direct set TLx, THx registers implemented
* Does not recompile examples every time. Compile only when it changed
* Compiler output suppressed for examples building in non verbose mode

0.10.0
* Fix compilation on Windows OS. Rename folder from aux to auxiliary
* Fix doxygen warnings
* Build examples hex
    * bits_example
    * chip_id_example
    * delay
    * frequency
    * interrupt
    * memory dumper
    * pin mode
    * pin value
    * power management
    * reset
    * timer
        * aux timer0
        * aux timer2
        * common
        * mode0
            * timer0
                * async
                * sync
        * mode1
            * async
            * sync
        * mode2
            * async
            * sync
        * mode3
            * async
            * sync
    * uart
    * wdt               

* Wrap multiline macro with do .. while(0)
    * chip_id.h
    * delay.h
    * frequency.h
    * pin.h

* Fix examples/timer/auxiliary/timer0/timer0_12T_freq_uint16_example.c. Its print garbage. And fix other freq and ticks - incorrect calculation.
* Fix direct setting TMOD. timer init should be used.
* Review watch dog timer routines. Current init with ticks have not intuitively understandable
* Update lib version in README.md  

Next releases todo
* TODO Implement counters
* TODO Implement UART
* TODO Optimize timer2 baud rate calculation. Use precalculated array of baudrates
* TODO Implement P5.4 as MCU reset source

