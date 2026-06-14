# Memory Dumper

A utility for dumping the first 256 bytes of **IDATA** (internal RAM) and **XDATA** (external RAM) memory spaces to UART1 on STC15 microcontrollers.

## Overview

This utility reads memory from address `0x00` to `0xFF` in both the IDATA and XDATA address spaces and outputs a formatted hex dump over UART1 at **115200 baud**.

## Output Format

The dump is printed in a standard hex dump format with 16 bytes per row:

```
IDATA:
    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00 |00|01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|
10 |10|11|12|13|14|15|16|17|18|19|1A|1B|1C|1D|1E|1F|
...
    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F

XDATA:
    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00 |00|01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|
...
    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
```

- The first column shows the row offset address in hexadecimal
- Each subsequent column shows the byte value at that offset
- The header and footer rows show column indices 0 through F

## Building

### With CMake

```bash
cmake -B build
cmake --build build --target mem_dump
```

### With PlatformIO / SCons

```bash
pio run -e your_env -t mem_dump
```

## Flashing

### With CMake

```bash
cmake --build build --target flash_mem_dump
```

This uses `stcgal` to flash the generated `.hex` file. Cycle power on the MCU when prompted.

## Files

| File | Description |
|------|-------------|
| [`mem_dump.c`](mem_dump.c) | Main entry point — initializes UART and dumps IDATA/XDATA |
| [`mem_print.c`](mem_print.c) | Hex dump formatting functions |
| [`mem_print.h`](mem_print.h) | Header for formatting functions |
| [`CMakeLists.txt`](CMakeLists.txt) | CMake build configuration |
| [`SConscript`](SConscript) | SCons build configuration for PlatformIO |

## Dependencies

- [`uart.h`](../../include/uart.h) — UART1 initialization and `putchar()` for `printf_tiny`
- SDCC (Small Device C Compiler) — for `__idata`, `__xdata`, `__code` keywords