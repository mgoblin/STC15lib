/*
 * Host tests for the SPI HAL (include/spi.h).
 *
 * These tests compile the real header against test/stubs/compiler.h and assert
 * the exact register values the macros produce. They cover the parts of the
 * module that are pure logic: bit masks, shifts, enum encodings and token
 * pasting. They do not and cannot verify 8051 hardware behaviour (see the
 * limitations noted in test/stubs/compiler.h).
 *
 * Expected values are derived from the STC15 series datasheet register tables:
 *
 *   P_SW1   A2H  S1_S1 S1_S0 CCP_S1 CCP_S0 SPI_S1 SPI_S0 0 DPS
 *   SPCTL   CEH  SSIG  SPEN  DORD MSTR CPOL CPHA SPR1 SPR0
 *   SPSTAT  CDH  SPIF  WCOL  - - - - - -
 *
 * Two hardware behaviours the stub cannot model, and how the tests cope:
 *
 *   - SPSTAT flags are cleared by writing 1 to them. The stub is plain memory,
 *     so bit_set(SPSTAT, mask) leaves the bits set rather than clearing them.
 *     The tests assert that the clear mask is written into SPSTAT, not that
 *     the bits read back as cleared.
 *
 *   - Hardware raises SPIF when a transfer finishes. The stub never does, so
 *     the tests set SPIF by hand to model a completed transfer. The sync
 *     routines poll SPIF until it appears, so they cannot be exercised here
 *     at all; only the non blocking async routines are covered.
 *
 * Run: ctest --test-dir <build> -V   (see test/CMakeLists.txt)
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <spi.h>
#include <pca.h>

static int failures = 0;
static int checks = 0;

#define CHECK_EQ(actual, expected, what)                               \
do {                                                                   \
    checks++;                                                          \
    unsigned long a_ = (unsigned long)(actual);                        \
    unsigned long e_ = (unsigned long)(expected);                      \
    if (a_ != e_) {                                                    \
        failures++;                                                    \
        printf("FAIL %s:%d  %s: got 0x%02lX, expected 0x%02lX\n",      \
               __FILE__, __LINE__, (what), a_, e_);                    \
    }                                                                  \
} while(0)

/* ---------------------------------------------------------------- pin group */

static void test_pin_group(void)
{
    /* SPI_S1:SPI_S0 are P_SW1 bits 3:2. They sit BELOW the CCP bits (5:4) and
       BELOW the UART1/S1 bits (7:6), so a group change must touch neither.
       Bits 7:6 are S1_S1:S1_S0, not SPI: writing those silently moves UART1
       to different pins. */
    P_SW1 = 0xFF;
    spi_set_pin_group(SPI_PIN_GROUP_1);         /* 00 */
    CHECK_EQ(P_SW1, 0xF3, "group 1 clears SPI bits, keeps others");

    P_SW1 = 0xFF;
    spi_set_pin_group(SPI_PIN_GROUP_2);         /* 01 */
    CHECK_EQ(P_SW1, 0xF7, "group 2 sets bit 2 only");

    P_SW1 = 0xFF;
    spi_set_pin_group(SPI_PIN_GROUP_3);         /* 10 */
    CHECK_EQ(P_SW1, 0xFB, "group 3 sets bit 3 only");

    /* From the power on reset value 0x40 (UART1 on P3.6/P3.7) UART1 must stay
       put for every SPI group. */
    P_SW1 = 0x40;
    spi_set_pin_group(SPI_PIN_GROUP_1);
    CHECK_EQ(P_SW1, 0x40, "group 1 keeps UART1 on reset pins");

    P_SW1 = 0x40;
    spi_set_pin_group(SPI_PIN_GROUP_2);
    CHECK_EQ(P_SW1, 0x44, "group 2 keeps UART1 on reset pins");

    P_SW1 = 0x40;
    spi_set_pin_group(SPI_PIN_GROUP_3);
    CHECK_EQ(P_SW1, 0x48, "group 3 keeps UART1 on reset pins");
}

static void test_pin_group_round_trip(void)
{
    P_SW1 = 0x00;
    spi_set_pin_group(SPI_PIN_GROUP_1);
    CHECK_EQ(spi_get_pin_group(), SPI_PIN_GROUP_1, "get group 1");

    P_SW1 = 0x00;
    spi_set_pin_group(SPI_PIN_GROUP_2);
    CHECK_EQ(spi_get_pin_group(), SPI_PIN_GROUP_2, "get group 2");

    P_SW1 = 0x00;
    spi_set_pin_group(SPI_PIN_GROUP_3);
    CHECK_EQ(spi_get_pin_group(), SPI_PIN_GROUP_3, "get group 3");
}

static void test_pin_group_coexists_with_pca(void)
{
    /* SPI and CCP share P_SW1. Selecting one must not disturb the other. */
    P_SW1 = 0x00;
    pca_set_pin_group(PCA_PIN_GROUP_3);         /* bits 5:4 -> 0x20 */
    spi_set_pin_group(SPI_PIN_GROUP_2);         /* bits 3:2 -> 0x04 */
    CHECK_EQ(P_SW1, 0x24, "PCA and SPI groups coexist");
    CHECK_EQ(pca_get_pin_group(), PCA_PIN_GROUP_3, "PCA group survives SPI change");
    CHECK_EQ(spi_get_pin_group(), SPI_PIN_GROUP_2, "SPI group survives PCA change");
}

/* ------------------------------------------------------------------- SPCTL */

static void test_init_master(void)
{
    /* SPEN | MSTR, then mode, clock, data order, and SSIG when CPHA=1. */
    spi_init_master(SPI_PIN_GROUP_1, SPI_MODE_0, SPI_CLOCK_DIV_16, false);
    CHECK_EQ(SPCTL, 0x51, "master mode 0, /16, MSB first");

    spi_init_master(SPI_PIN_GROUP_1, SPI_MODE_1, SPI_CLOCK_DIV_4, true);
    CHECK_EQ(SPCTL, 0xF4, "master mode 1, /4, LSB first sets DORD and SSIG");

    spi_init_master(SPI_PIN_GROUP_1, SPI_MODE_2, SPI_CLOCK_DIV_64, false);
    CHECK_EQ(SPCTL, 0x5A, "master mode 2, /64, MSB first");

    spi_init_master(SPI_PIN_GROUP_1, SPI_MODE_3, SPI_CLOCK_DIV_128, true);
    CHECK_EQ(SPCTL, 0xFF, "master mode 3, /128, LSB first");

    CHECK_EQ(is_spi_enabled(), 1, "master is enabled");
    CHECK_EQ(is_spi_master(), 1, "master reports master");
}

static void test_init_slave(void)
{
    /* SPEN only: no MSTR and no SSIG, the SS pin selects the device and the
       clock divider is unused because the master clocks the bus. */
    spi_init_slave(SPI_PIN_GROUP_1, SPI_MODE_0, false);
    CHECK_EQ(SPCTL, 0x40, "slave mode 0, MSB first");

    spi_init_slave(SPI_PIN_GROUP_1, SPI_MODE_1, true);
    CHECK_EQ(SPCTL, 0x64, "slave mode 1, LSB first");

    spi_init_slave(SPI_PIN_GROUP_1, SPI_MODE_2, false);
    CHECK_EQ(SPCTL, 0x48, "slave mode 2, MSB first");

    spi_init_slave(SPI_PIN_GROUP_1, SPI_MODE_3, true);
    CHECK_EQ(SPCTL, 0x6C, "slave mode 3, LSB first");

    CHECK_EQ(is_spi_enabled(), 1, "slave is enabled");
    CHECK_EQ(is_spi_master(), 0, "slave reports slave");
}

static void test_destroy(void)
{
    spi_init_master(SPI_PIN_GROUP_1, SPI_MODE_1, SPI_CLOCK_DIV_4, false);
    SPSTAT = 0x00;
    spi_destroy();
    CHECK_EQ(SPCTL, 0x00, "destroy disables SPI");
    CHECK_EQ(SPSTAT, SPI_SPSTAT_CLEAR_MSK, "destroy writes the flag clear mask");
    CHECK_EQ(is_spi_enabled(), 0, "destroyed SPI reports disabled");
}

/* ------------------------------------------------------------- mode/clock */

static void test_get_mode_and_clock(void)
{
    SPCTL = 0x00;
    CHECK_EQ(spi_get_mode(), SPI_MODE_0, "get mode 0");
    CHECK_EQ(spi_get_clock(), SPI_CLOCK_DIV_4, "get /4");

    SPCTL = 0x0C;
    CHECK_EQ(spi_get_mode(), SPI_MODE_3, "get mode 3 from CPOL|CPHA bits");

    SPCTL = 0x03;
    CHECK_EQ(spi_get_clock(), SPI_CLOCK_DIV_128, "get /128 from SPR bits");

    /* Mode and clock occupy disjoint bits, so both survive together. */
    SPCTL = 0x0B;
    CHECK_EQ(spi_get_mode(), SPI_MODE_2, "mode reads back with clock bits set");
    CHECK_EQ(spi_get_clock(), SPI_CLOCK_DIV_128, "clock reads back with mode bits set");
}

/* --------------------------------------------------------------- transfers */

static void test_async_transfer(void)
{
    SPCTL = SPI_SPEN_MSK | SPI_MSTR_MSK;

    SPSTAT = 0x00;
    spi_async_transfer_start(0x7E);
    CHECK_EQ(SPDAT, 0x7E, "async start loads the data register");
    CHECK_EQ(SPSTAT, SPI_SPSTAT_CLEAR_MSK, "async start writes the flag clear mask");

    /* Model a transfer still in flight: hardware has not raised SPIF yet. */
    SPSTAT = 0x00;
    CHECK_EQ(is_spi_async_transfer_complete(), 0, "not complete while SPIF clear");

    /* Hardware raises SPIF when the byte has shifted out. */
    SPSTAT = SPI_SPIF_MSK;
    CHECK_EQ(is_spi_async_transfer_complete(), 1, "complete when SPIF set");
    CHECK_EQ(spi_async_get_result(), 0x7E, "async result is the data register");

    SPSTAT = 0x00;
    spi_async_transfer_finish();
    CHECK_EQ(SPSTAT, SPI_SPSTAT_CLEAR_MSK, "finish writes the flag clear mask");
}

static void test_write_collision(void)
{
    SPSTAT = 0x00;
    CHECK_EQ(is_spi_write_collision(), 0, "no collision when WCOL clear");

    SPSTAT = SPI_WCOL_MSK;
    CHECK_EQ(is_spi_write_collision(), 1, "collision when WCOL set");

    spi_async_transfer_finish();
    CHECK_EQ(SPSTAT, SPI_WCOL_MSK | SPI_SPSTAT_CLEAR_MSK,
             "finish writes the flag clear mask over WCOL");
}

/* ----------------------------------------------------------- slave select */

static void test_slave_select(void)
{
    P1 = 0xFF;
    spi_ss_clr(SPI_PIN_GROUP_1);
    CHECK_EQ(P1, 0xFB, "SS on P1.2 pulled low");

    spi_ss_set(SPI_PIN_GROUP_1);
    CHECK_EQ(P1, 0xFF, "SS on P1.2 pulled high");

    P2 = 0xFF;
    spi_ss_clr(SPI_PIN_GROUP_2);
    CHECK_EQ(P2, 0xEF, "SS_2 on P2.4 pulled low");

    spi_ss_set(SPI_PIN_GROUP_2);
    CHECK_EQ(P2, 0xFF, "SS_2 on P2.4 pulled high");

    P5 = 0xFF;
    spi_ss_clr(SPI_PIN_GROUP_3);
    CHECK_EQ(P5, 0xEF, "SS_3 on P5.4 pulled low");

    spi_ss_set(SPI_PIN_GROUP_3);
    CHECK_EQ(P5, 0xFF, "SS_3 on P5.4 pulled high");
}

/* --------------------------------------------------------------------- main */

int main(void)
{
    test_pin_group();
    test_pin_group_round_trip();
    test_pin_group_coexists_with_pca();
    test_init_master();
    test_init_slave();
    test_destroy();
    test_get_mode_and_clock();
    test_async_transfer();
    test_write_collision();
    test_slave_select();

    printf("%s: %d check(s), %d failure(s)\n",
           failures ? "FAILED" : "ALL PASSED", checks, failures);

    return failures != 0;
}
