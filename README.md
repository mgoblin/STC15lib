# What it is
This C-library contains hardware abstraction layer (HAL) for STC15W408AS. 

STC15W408AS is a micro chip compatible with 8051 architecture.

# How to use it
This code is published as [Platformio](https://platformio.org/) library named STC15 hardware.

## Add library to your project
After create Platformio project for STC15408AS add to platformio.ini line with library depandency

```ini
[env:STC15W408AS]
platform = intel_mcs51
board = STC15W408AS
lib_deps = mgoblin/STC15 hardware@^0.12.0
```
Where is 0.12.0 STC15 hardware library version.

As alternative in lib_deps line github link could be used.

```ini
[env:STC15W408AS]
platform = intel_mcs51
board = STC15W408AS
lib_deps = https://github.com/mgoblin/STC15lib#0.12.0
```

Where is 0.12.0 STC15 hardware library github tag version.

Each released library version has the tag in github repository. 

## Low level STC15 prorgamming
You can directly manipulate to MCU registers from C-code. 
STC15Fxx.h should be included. 

```C
#include <STC15Fxx.h> // MCU SFR declarations 

void main()
{
    // Use SFR declaration to change MCU state here

    P10 = 0; // As example put LED on. Pin P1.0 connected to onboard LED
}
```

## Use STC15 HAL functions
This library provides hardware astraction laywer (HAL) for high level development tasks.
Please read the docs for library modules in Library documentation section (see the docs link).

Most of HAL functionality is C-macros. 

The advantage is small firmware code size because 
macroses are expanded into application.

C-Macroses have some drawbacks.

1. No compiler typechecks
2. No function call optimizations. Macroses code inlined.

If you need to use one HAL macros many times the good idea is to wrap macros by C-function.

```C
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

// Wrap delay_ms HAL macros call to C-function
void f_delay_ms(uint16_t ms)
{
    delay_ms(ms); // This is a macros 
} 

void main()
{
    while(1)
    {
        LED = ON;
        f_delay_ms(500);
        LED = OFF;
        f_delay_ms(1000);
    }
}
```

# Library modules maturity
| Module name  | Description                      | Maturity           |
|------------- |----------------------------------|--------------------|
| ChipID       | Get chip id from ROM             | READY              |
| Delay        | CPU cycles based delay           | READY              |
| CPU frequency| CPU frequency slowdown           | READY              |
| Interrupt    | Enable and disable interrupts    | READY              |
| Power management | idle, powerdown and wakeup timer        | READY              |
| Reset        | Software reset                   | READY              |
| Timer        | Timer control routines           | READY              |
| Counter      | Counter control routines         | READY              |
| UART         | Serial port p-2-p routines             | PARTIAL SUPPORT (only mode 0, 1, 2)    |
| Watchdog timer | Watchdog timer routines        | READY              |
| Pin          | Pin as digital in/out routines   | READY              |

Other modules does not implemented yet.

See examples in [https://github.com/mgoblin/STC15lib/tree/main/examples](https://github.com/mgoblin/STC15lib/tree/main/examples)

# Library documentation
[Docs](https://mgoblin.github.io/STC15lib/docs/html/index.html)

# Version history
[Version history](https://mgoblin.github.io/STC15lib/VERSION_HISTORY.html)

# References

* STC datasheets: [http://stcmicro.com/sjsc.html](http://stcmicro.com/sjsc.html)
* SDCC User Guide (PDF): [http://sdcc.sourceforge.net/doc/sdccman.pdf](http://sdcc.sourceforge.net/doc/sdccman.pdf)
* STC programmator [https://github.com/mgoblin/STC-programmatorhttps://github.com/mgoblin/STC-programmator](https://github.com/mgoblin/STC-programmatorhttps://github.com/mgoblin/STC-programmator)
