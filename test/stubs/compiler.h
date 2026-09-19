/*
 * Host build stub for the SDCC mcs51 <compiler.h>.
 *
 * SDCC defines SFR() and SBIT() in terms of the __sfr and __sbit keywords,
 * which bind a name to an absolute 8051 address. A host compiler has no such
 * keywords, so this stub declares each name as an ordinary volatile byte.
 *
 * The stub exists so the pure logic in the HAL headers (bit masks, shifts,
 * token pasting, enum encodings) can be compiled and asserted on the host,
 * independently of the 8051 target. A test includes the real header, runs a
 * macro, then asserts on the register the macro names:
 *
 *     pca_set_clock_source(PCA_CLOCK_SYS);
 *     assert(CMOD == 0x08);
 *
 * WHAT THIS STUB MODELS
 *   - SFR and SBIT names are declared lvalues, so the real headers compile
 *     unchanged and a test can assert the exact value a macro assigned.
 *
 * WHAT THIS STUB DOES NOT MODEL
 *   - Addresses. Each name is separate storage, so two names sharing one
 *     address (AUXR1 and P_SW1 are both 0xA2) are independent here. Only the
 *     name a macro actually writes is meaningful in a test.
 *   - Bit aliasing. A real 8051 __sbit lives inside its parent SFR byte, so
 *     "CF = 0" clears bit 7 of CCON. Here SBIT names are separate bytes, so a
 *     test can observe that a named bit was assigned, but not that it landed
 *     in the parent register. Bit positions are verified against the
 *     datasheet, not by this stub.
 *   - Peripheral behaviour. There is no PCA counter, no SPI shift register
 *     and no timer; registers are plain memory.
 *
 * This stub is used by test/ only. Firmware builds use the real SDCC
 * <compiler.h> and never see this file.
 */
#ifndef STC15_HOST_COMPILER_STUB_H
#define STC15_HOST_COMPILER_STUB_H

#include <stdint.h>

/*
 * SDCC emits "SFR(NAME, addr);" as a declaration, so the host macro must also
 * be a declaration. The address argument is intentionally unused on the host.
 */
#define SFR(name, addr) volatile uint8_t name
#define SBIT(name, addr, bit) volatile uint8_t name

#endif
