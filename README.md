# STC15 Hardware Abstraction Layer (STC15 HAL)

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/mgoblin/library/STC15%20hardware.svg)](https://registry.platformio.org/libraries/mgoblin/STC15%20hardware)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

A lightweight C Hardware Abstraction Layer (HAL) and register definition library for **STC15 series** microcontrollers (specifically optimized for **STC15W408AS** and MCS51/8051-compatible devices) using the **SDCC (Small Device C Compiler)** toolchain.

---


## Overview

The STC15 HAL provides hardware abstractions for the STC15W408AS microcontroller series. Due to the strict flash and RAM constraints of 8051 microcontrollers, most HAL routines are implemented as efficient **C macros** that expand directly in-place to minimize call overhead and eliminate runtime function call penalty. Supporting modules for tick/frequency conversions and mathematical tables are compiled into a compact static library (`stc15hal.lib`).

---

## For Firmware Developers

### Installation & Integration

#### PlatformIO

Add the library to your `platformio.ini` configuration file:

```ini
[env:STC15W408AS]
platform = intel_mcs51
board = STC15W408AS
lib_deps = mgoblin/STC15 hardware@^0.18.0
```

Alternatively, you can depend directly on a GitHub release tag or branch:

```ini
[env:STC15W408AS]
platform = intel_mcs51
board = STC15W408AS
lib_deps = https://github.com/mgoblin/STC15lib.git#0.18.0
```

#### CMake / Standalone SDCC

Include the `include/` directory in your compiler header search paths and link against `stc15hal.lib` (built from `src/`).

### Architecture: Direct SFR vs. HAL Macros

#### 1. Direct SFR Manipulation
You can directly read and modify Special Function Registers (SFRs) by including `<STC15Fxx.h>`:

```c
#include <STC15Fxx.h>

void main(void) {
    P10 = 0; // Set P1.0 LOW (e.g., turn on active-low onboard LED)
}
```

#### 2. HAL Macros & Size Optimization
The HAL macros offer descriptive names, bitmask operations, and automated register setup:

- **Advantage:** Generates minimal, fast assembly by avoiding stack frame creation.
- **Trade-off:** Inlined code increases flash size if a large macro is called repeatedly in many places.
- **Best Practice:** If you call a multi-line macro frequently, wrap it in a small helper C function:

```c
#include <delay.h>
#include <gpio.h>

// Wrap delay_ms macro in a function to avoid inlining overhead across multiple call sites
void sleep_ms(uint16_t ms) {
    delay_ms(ms);
}
```

### Module Status & Maturity

| Module               | Header                | Description                                                                      | Maturity        |
|----------------------|-----------------------|----------------------------------------------------------------------------------|-----------------|
| **Chip ID**          | `chip_id.h`           | Read unique 7-byte hardware ID from MCU ROM                                      | Ready           |
| **Delay**            | `delay.h`             | Accurate millisecond and microsecond delays                                      | Ready           |
| **CPU Frequency**    | `frequency.h`         | Master clock prescaler & clock output to pins (P5.4, P1.6)                       | Ready           |
| **Interrupts**       | `interrupt.h`         | Global/peripheral interrupt enable, priority, INT0/INT1 triggers                 | Ready           |
| **Power Management** | `power_management.h`  | Idle mode, Power-Down mode, Wake-Up timer, Low-voltage detection                 | Ready           |
| **Reset**            | `reset.h`             | Software system reset to AP or IAP                                               | Ready           |
| **Timer 0**          | `timer0_mode*.h`      | Modes 0, 1, 2, 3 in 1T/12T, sync delays, async interrupts, ms/ticks conversions  | Ready           |
| **Timer 2**          | `timer2_mode0.h`      | Mode 0 (16-bit auto-reload) in 1T/12T, baud generator, sync/async                | Ready           |
| **Counters**         | `counter*.h`          | External event counter on Timer0 (Modes 0-3) and Timer2 (Mode 0)                 | Ready           |
| **UART1**            | `uart.h`, `uart1_*.h` | Modes 0, 1 (Timer2 1T/12T), 2, 3; stdio integration (`putchar`, `printf_tiny`)   | Ready           |
| **Watchdog Timer**   | `wdt.h`               | Hardware watchdog prescaler, enable, and feed                                    | Ready           |
| **GPIO**             | `gpio.h`              | Port modes (quasi-bidirectional, push-pull, input-only, open-drain) & pin access | Ready           |
| **EEPROM / IAP**     | `eeprom.h`            | Read byte, write byte/array, and sector erase via IAP registers                  | Ready           |
| **ADC**              | `adc.h`               | 10-bit analog-to-digital converter (sync blocking and async interrupt modes)     | Ready           |
| **Comparator**       | `comparator.h`        | On-chip analog voltage comparator                                                | Initial Support |
| **PCA / CCP**        | `pca.h`               | 16-bit counter, compare/capture, high-speed toggle output, 8/7/6-bit PWM         | Initial Support |
| **SPI**              | `spi.h`               | Master & slave, 3 pin groups, 4 clock dividers, CPOL/CPHA modes, sync & async    | Initial Support |
| **Bit Operations**   | `bits.h`              | Fast bit set, clear, toggle, and test macros                                     | Ready           |

### Code Examples

See examples subfolder. 


#### 1. GPIO & Delays (Blink LED)

```c
#include <gpio.h>
#include <delay.h>

#define LED_PIN 0 // P1.0

void main(void) {
    // Configure P1.0 as push-pull output
    pin_push_pull_init(P1, LED_PIN);

    while (1) {
        pin_set_low(P1, LED_PIN);   // LED ON (active low)
        delay_ms(500);
        pin_set_high(P1, LED_PIN);  // LED OFF
        delay_ms(500);
    }
}
```

#### 2. UART1 Serial Communication & printf

```c
#include <uart.h>
#include <stdio.h>
#include <delay.h>

void main(void) {
    // Initialize UART1 at 9600 baud using Timer2 (1T mode) on P3.0 (RxD) and P3.1 (TxD)
    uart1_init(9600);

    while (1) {
        printf_tiny("Hello from STC15 HAL!\r\n");
        delay_ms(1000);
    }
}
```

#### 3. 10-bit ADC (Analog-to-Digital Converter)

```c
#include <adc.h>
#include <uart.h>
#include <stdio.h>

#define ADC_CHANNEL_PIN 1 // ADC channel on P1.1

void main(void) {
    uart1_init(115200);

    // Initialize P1.1 as high-impedance input for ADC, standard bit order, 90 cycle conversion speed
    adc_init_input_only(ADC_CHANNEL_PIN, false, ADC_SPEED_90);

    while (1) {
        uint16_t adc_val;
        adc_read_sync(&adc_val);
        printf_tiny("ADC Value (P1.1): %u\r\n", adc_val);
        delay_ms(250);
    }
}
```

#### 4. Timers & Interrupts

```c
#include <timer0_mode0.h>
#include <interrupt.h>

// Timer0 overflow interrupt service routine (Interrupt Vector 1)
void timer0_isr(void) __interrupt(1) {
    P10 = !P10; // Toggle P1.0
}

void main(void) {
    // Configure Timer0 in Mode 0 (16-bit auto-reload), 12T mode, starting with 1000 ticks
    timer0_mode0_12T_init();
    timer0_mode0_start(1000);

    // Enable Timer0 interrupt and global interrupts
    timer0_mode0_enable_interrupt();
    enable_mcu_interrupts();

    while (1) {
        // Main loop
    }
}
```

#### 5. On-Chip EEPROM (IAP) Read / Write / Erase

```c
#include <eeprom.h>
#include <uart.h>
#include <stdio.h>

void main(void) {
    uart1_init(115200);

    uint16_t sector_addr = 0x0000;
    
    // 1. Sector erase (required before writing new data)
    eeprom_erase_page(sector_addr);

    // 2. Write a single byte
    eeprom_write_byte(sector_addr, 0x42);

    // 3. Read back written byte
    uint8_t val = eeprom_read_byte(sector_addr);
    printf_tiny("Read EEPROM: 0x%x\r\n", val);

    while (1);
}
```

### Flashing Firmware

Flashing can be done using [`stcgal`](https://github.com/grigorig/stcgal):

```bash
stcgal -P stc15 your_firmware.hex
```

When prompted by `stcgal`, power-cycle the target MCU board to initiate ISP flashing.

---

## For Contributors & Library Developers

### Prerequisites

Ensure the following tools are installed:
- **SDCC** (Small Device C Compiler): version 4.1, 4.5, or 4.6 (default configured: 4.5)
- **CMake** (3.31+) & **Ninja** / **Make**
- **Python 3** (for size calculation and summary scripts)
- **Doxygen** & **Graphviz** (for documentation generation)
- **PlatformIO Core (CLI)** (for PlatformIO builds)
- **stcgal** (for hardware flashing)

### Building with CMake

1. **Configure the build** using the SDCC toolchain file:

   ```bash
   cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-SDCC.cmake
   ```

2. **Build the HAL static library, all examples, and utilities:**

   ```bash
   cmake --build build
   ```

3. **View the build summary & firmware sizes:**

   During the build, `cmake_examples_build_summary.py` automatically generates a table of compiled `.hex` files and memory usage (FLASH/ROM, IDATA, XDATA). You can view the summary with:

   ```bash
   cmake --build build --target print_build_summary
   ```

4. **Build Doxygen documentation:**

   ```bash
   cmake --build build --target docs
   ```

5. **Flash an example directly:**

   ```bash
   cmake --build build --target flash_delay
   cmake --build build --target flash_adc_read
   ```

### Building with PlatformIO

The project includes custom build scripts located in `platformio_build/`:
- `compile_lib.py`: Compiles the core STC15 HAL library.
- `compile_examples.py`: Compiles all examples and outputs a firmware size summary.
- `compile_utils.py`: Builds standalone utilities.
- `doxygen.py`: Generates Doxygen HTML docs.

To run the full PlatformIO build pipeline:

```bash
pio run
```

### Utilities

The repository includes utilities located in `utils/`:

#### Memory Dumper
- **Location:** `utils/memory_dumper`
- **Purpose:** Diagnostic firmware that dumps the first 256 bytes of MCU **IDATA** and **XDATA** memory spaces over UART1 at **115200 baud** in a formatted hex matrix.
- **Build:** `cmake --build build --target mem_dump`
- **Flash:** `cmake --build build --target flash_mem_dump`

#### CSV to HEX Converter (csv2hex)
- **Location:** `utils/csv2hex`
- **Purpose:** A Python-based CLI tool (managed with Poetry) that transforms CSV data tables into standard Intel HEX files suitable for flashing directly into EEPROM/Flash data sectors.

### Project Layout

```text
STC15/
├── cmake/               # CMake toolchains (SDCC), memory size scripts, build helpers
├── platformio_build/    # PlatformIO SCons build scripts (lib, examples, utils, docs)
├── include/             # Public HAL C headers and register definitions (<STC15Fxx.h>, etc.)
├── src/                 # C source files compiled into stc15hal.lib (UART, timer math tables)
├── examples/            # Categorized example programs for all peripherals
│   ├── adc/             # ADC read & interrupt examples + wiring schema
│   ├── comparator/      # Voltage comparator examples
│   ├── counter/         # Counter0 and Counter2 mode examples
│   ├── delay/           # Delay calibration examples
│   ├── eeprom/          # EEPROM read, write byte/page, erase examples
│   ├── gpio/            # GPIO pin modes and values examples
│   ├── interrupt/       # External interrupt & priority examples
│   ├── pca/             # PCA/CCP: PWM, 16-bit timer, and capture examples
│   ├── power_management/# Idle, Power-Down, and Wake-up timer examples
│   ├── spi/             # SPI master & slave examples
│   ├── timer/           # Timer0 & Timer2 mode examples (sync & async)
│   └── uart/            # UART1 modes 0, 1, 2, 3 examples
├── test/                # Host tests for the library headers (ctest)
├── utils/               # Diagnostic and data conversion tools (mem_dump, csv2hex)
├── docs/                # Generated Doxygen documentation
├── doxygen.conf         # Doxygen documentation configuration
├── library.json         # PlatformIO library specification
├── platformio.ini       # PlatformIO project environment configuration
├── CMakeLists.txt       # Root CMake build configuration
└── CHANGELOG.md         # Release history and roadmap
```

---

## Documentation & Changelog

- **API Documentation:** [https://mgoblin.github.io/STC15lib/index.html](https://mgoblin.github.io/STC15lib/index.html)
- **Change Log:** [CHANGELOG.md](CHANGELOG.md) or [Online Changelog](https://mgoblin.github.io/STC15lib/md_CHANGELOG.html)

---

## References

- **STC Microcontroller Datasheets:** [http://stcmicro.com/sjsc.html](http://stcmicro.com/sjsc.html)
- **SDCC User Guide:** [http://sdcc.sourceforge.net/doc/sdccman.pdf](http://sdcc.sourceforge.net/doc/sdccman.pdf)
- **stcgal (STC ISP Flasher):** [https://github.com/grigorig/stcgal](https://github.com/grigorig/stcgal)
- **STC-programmator:** [https://github.com/mgoblin/STC-programmator](https://github.com/mgoblin/STC-programmator)

---

## License

This project is licensed under the [Apache License 2.0](LICENSE).
