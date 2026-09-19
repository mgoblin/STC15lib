/*
 * Host tests for the PCA/CCP HAL (include/pca.h).
 *
 * These tests compile the real header against test/stubs/compiler.h and assert
 * the exact register values the macros produce. They cover the parts of the
 * module that are pure logic: bit masks, shifts, enum encodings and token
 * pasting. They do not and cannot verify 8051 hardware behaviour (see the
 * limitations noted in test/stubs/compiler.h).
 *
 * Expected values are derived from the STC15 series datasheet register tables:
 *
 *   CMOD    D9H  CIDL  -  -  -  CPS2 CPS1 CPS0 ECF
 *   CCON    D8H  CF    CR  -  -  -   CCF2 CCF1 CCF0
 *   CCAPMn  DAH  -  ECOMn CAPPn CAPNn MATn TOGn PWMn ECCFn
 *   PCA_PWMn F2H EBSn_1 EBSn_0 - - - - EPCnH EPCnL
 *   P_SW1   A2H  S1_S1 S1_S0 CCP_S1 CCP_S0 SPI_S1 SPI_S0 0 DPS
 *
 * Run: ctest --test-dir <build> -V   (see test/CMakeLists.txt)
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    /* CCP_S1:CCP_S0 are P_SW1 bits 5:4. Selecting a group must clear both
       bits first, then set the requested value, leaving other bits alone. */
    P_SW1 = 0xFF;
    pca_set_pin_group(PCA_PIN_GROUP_1);         /* 00 */
    CHECK_EQ(P_SW1, 0xCF, "P_SW1 group 1 clears CCP bits, keeps others");

    P_SW1 = 0x00;
    pca_set_pin_group(PCA_PIN_GROUP_2);         /* 01 -> bit4 */
    CHECK_EQ(P_SW1, 0x10, "P_SW1 group 2 sets bit 4");

    P_SW1 = 0x00;
    pca_set_pin_group(PCA_PIN_GROUP_3);         /* 10 -> bit5 */
    CHECK_EQ(P_SW1, 0x20, "P_SW1 group 3 sets bit 5");

    /* Enum encodings match the datasheet bit patterns. */
    CHECK_EQ(PCA_PIN_GROUP_1, 0, "PCA_PIN_GROUP_1 encoding");
    CHECK_EQ(PCA_PIN_GROUP_2, 1, "PCA_PIN_GROUP_2 encoding");
    CHECK_EQ(PCA_PIN_GROUP_3, 2, "PCA_PIN_GROUP_3 encoding");

    /* Read back through the getter. */
    P_SW1 = 0x00;
    pca_set_pin_group(PCA_PIN_GROUP_3);
    CHECK_EQ(pca_get_pin_group(), PCA_PIN_GROUP_3, "pca_get_pin_group reads 3");
    pca_set_pin_group(PCA_PIN_GROUP_2);
    CHECK_EQ(pca_get_pin_group(), PCA_PIN_GROUP_2, "pca_get_pin_group reads 2");
    pca_set_pin_group(PCA_PIN_GROUP_1);
    CHECK_EQ(pca_get_pin_group(), PCA_PIN_GROUP_1, "pca_get_pin_group reads 1");
}

/* ------------------------------------------------------------ clock source */

static void test_clock_source(void)
{
    /* CPS2:CPS1:CPS0 are CMOD bits 3:1. */
    CMOD = 0x00;
    pca_set_clock_source(PCA_CLOCK_SYS);        /* 4 -> 4<<1 = 0x08 */
    CHECK_EQ(CMOD, 0x08, "CMOD SYSclk");

    CMOD = 0x00;
    pca_set_clock_source(PCA_CLOCK_SYS_12);     /* 0 */
    CHECK_EQ(CMOD, 0x00, "CMOD SYSclk/12");

    CMOD = 0x00;
    pca_set_clock_source(PCA_CLOCK_SYS_8);      /* 7 -> 0x0E */
    CHECK_EQ(CMOD, 0x0E, "CMOD SYSclk/8");

    /* ECF (bit 0) and CIDL (bit 7) must survive a clock source change. */
    CMOD = 0x81;                                /* CIDL=1, ECF=1 */
    pca_set_clock_source(PCA_CLOCK_TIMER0);     /* 2 -> 0x04 */
    CHECK_EQ(CMOD, 0x85, "CMOD keeps CIDL and ECF bits");

    /* Enum encodings match the datasheet CPS values. */
    CHECK_EQ(PCA_CLOCK_SYS_12, 0, "PCA_CLOCK_SYS_12 encoding");
    CHECK_EQ(PCA_CLOCK_SYS_2,  1, "PCA_CLOCK_SYS_2 encoding");
    CHECK_EQ(PCA_CLOCK_TIMER0, 2, "PCA_CLOCK_TIMER0 encoding");
    CHECK_EQ(PCA_CLOCK_ECI,    3, "PCA_CLOCK_ECI encoding");
    CHECK_EQ(PCA_CLOCK_SYS,    4, "PCA_CLOCK_SYS encoding");
    CHECK_EQ(PCA_CLOCK_SYS_4,  5, "PCA_CLOCK_SYS_4 encoding");
    CHECK_EQ(PCA_CLOCK_SYS_6,  6, "PCA_CLOCK_SYS_6 encoding");
    CHECK_EQ(PCA_CLOCK_SYS_8,  7, "PCA_CLOCK_SYS_8 encoding");

    /* Round trip through the getter for every source. */
    for (int src = 0; src <= 7; src++) {
        CMOD = 0x00;
        pca_set_clock_source((pca_clock_source_t)src);
        CHECK_EQ(pca_get_clock_source(), (unsigned)src,
                 "pca_get_clock_source round trip");
    }
}

/* ------------------------------------------------------------ counter value */

static void test_counter(void)
{
    /* CH is the high byte, CL the low byte. */
    pca_set_counter(0x1234);
    CHECK_EQ(CH, 0x12, "pca_set_counter high byte");
    CHECK_EQ(CL, 0x34, "pca_set_counter low byte");

    CHECK_EQ(pca_get_counter(), 0x1234, "pca_get_counter reads back");

    pca_set_counter(0x00FF);
    CHECK_EQ(CH, 0x00, "pca_set_counter 0x00FF high byte");
    CHECK_EQ(CL, 0xFF, "pca_set_counter 0x00FF low byte");
    CHECK_EQ(pca_get_counter(), 0x00FF, "pca_get_counter 0x00FF");

    pca_set_counter(0xFFFF);
    CHECK_EQ(pca_get_counter(), 0xFFFF, "pca_get_counter 0xFFFF");

    pca_set_counter(0x0000);
    CHECK_EQ(pca_get_counter(), 0x0000, "pca_get_counter 0x0000");
}

/* ------------------------------------------------------- run / idle control */

static void test_run_and_idle(void)
{
    /* CR is CCON bit 6, exposed as the named bit CR in STC15Fxx.h. */
    pca_stop();
    CHECK_EQ(is_pca_running(), 0, "is_pca_running false after stop");
    pca_start();
    CHECK_EQ(is_pca_running(), 1, "is_pca_running true after start");

    /* CIDL is CMOD bit 7. */
    pca_counter_run_in_idle();
    CHECK_EQ(CMOD & 0x80, 0x00, "CIDL cleared by run_in_idle");
    CHECK_EQ(is_pca_counter_gated_off_in_idle(), 0, "gated_off false after run_in_idle");

    pca_counter_gate_off_in_idle();
    CHECK_EQ(CMOD & 0x80, 0x80, "CIDL set by gate_off_in_idle");
    CHECK_EQ(is_pca_counter_gated_off_in_idle(), 1, "gated_off true after gate_off_in_idle");

    /* ECF is CMOD bit 0. */
    pca_disable_overflow_interrupt();
    CHECK_EQ(CMOD & 0x01, 0x00, "ECF cleared");
    CHECK_EQ(is_pca_overflow_interrupt_enabled(), 0, "overflow int disabled");
    pca_enable_overflow_interrupt();
    CHECK_EQ(CMOD & 0x01, 0x01, "ECF set");
    CHECK_EQ(is_pca_overflow_interrupt_enabled(), 1, "overflow int enabled");

    /* CF is CCON bit 7, cleared through the named bit. */
    CF = 1;
    CHECK_EQ(is_pca_overflow(), 1, "overflow flag set");
    pca_clear_overflow_flag();
    CHECK_EQ(is_pca_overflow(), 0, "overflow flag cleared");
}

/* ------------------------------------------------------- module bit control */

static void test_module_bits(void)
{
    /* Each module has its own CCAPMn register with identical bit layout. */
    CCAPM0 = 0x00;
    pca_module_enable_comparator(0);            /* ECOMn = bit 6 */
    CHECK_EQ(CCAPM0, 0x40, "module 0 ECOM bit 6");
    pca_module_disable_comparator(0);
    CHECK_EQ(CCAPM0, 0x00, "module 0 ECOM cleared");

    CCAPM1 = 0x00;
    pca_module_enable_capture_positive(1);      /* CAPPn = bit 5 */
    CHECK_EQ(CCAPM1, 0x20, "module 1 CAPP bit 5");
    pca_module_disable_capture_positive(1);
    CHECK_EQ(CCAPM1, 0x00, "module 1 CAPP cleared");

    CCAPM2 = 0x00;
    pca_module_enable_capture_negative(2);      /* CAPNn = bit 4 */
    CHECK_EQ(CCAPM2, 0x10, "module 2 CAPN bit 4");
    pca_module_disable_capture_negative(2);
    CHECK_EQ(CCAPM2, 0x00, "module 2 CAPN cleared");

    CCAPM0 = 0x00;
    pca_module_enable_match(0);                 /* MATn = bit 3 */
    CHECK_EQ(CCAPM0, 0x08, "module 0 MAT bit 3");
    pca_module_disable_match(0);
    CHECK_EQ(CCAPM0, 0x00, "module 0 MAT cleared");

    CCAPM1 = 0x00;
    pca_module_enable_toggle(1);                /* TOGn = bit 2 */
    CHECK_EQ(CCAPM1, 0x04, "module 1 TOG bit 2");
    pca_module_disable_toggle(1);
    CHECK_EQ(CCAPM1, 0x00, "module 1 TOG cleared");

    /* Interrupt enable is ECCFn = bit 0. */
    CCAPM2 = 0x00;
    pca_module_enable_interrupt(2);
    CHECK_EQ(CCAPM2, 0x01, "module 2 ECCF bit 0");
    CHECK_EQ(is_pca_module_interrupt_enabled(2), 1, "module 2 int enabled");
    pca_module_disable_interrupt(2);
    CHECK_EQ(CCAPM2, 0x00, "module 2 ECCF cleared");
    CHECK_EQ(is_pca_module_interrupt_enabled(2), 0, "module 2 int disabled");

    /* The token pasting must reach the right register per module. */
    CCAPM0 = 0x00; CCAPM1 = 0x00; CCAPM2 = 0x00;
    pca_module_enable_comparator(1);
    CHECK_EQ(CCAPM0, 0x00, "module 1 ECOM does not touch CCAPM0");
    CHECK_EQ(CCAPM1, 0x40, "module 1 ECOM hits CCAPM1");
    CHECK_EQ(CCAPM2, 0x00, "module 1 ECOM does not touch CCAPM2");

    /* CCON module flags CCF0..CCF2 are bits 0..2. */
    CCF0 = 1; CCF1 = 0; CCF2 = 0;
    CHECK_EQ(is_pca_module_flag_set(0), 1, "CCF0 set");
    CHECK_EQ(is_pca_module_flag_set(1), 0, "CCF1 clear");
    pca_clear_module_flag(0);
    CHECK_EQ(is_pca_module_flag_set(0), 0, "CCF0 cleared");
}

/* ---------------------------------------------------------- compare/capture */

static void test_compare_capture(void)
{
    /* CCAPnH is the high byte, CCAPnL the low byte. */
    pca_module_set_compare(0, 0xABCD);
    CHECK_EQ(CCAP0H, 0xAB, "module 0 compare high byte");
    CHECK_EQ(CCAP0L, 0xCD, "module 0 compare low byte");

    pca_module_set_compare(1, 0x1234);
    CHECK_EQ(CCAP1H, 0x12, "module 1 compare high byte");
    CHECK_EQ(CCAP1L, 0x34, "module 1 compare low byte");

    pca_module_set_compare(2, 0x00FF);
    CHECK_EQ(CCAP2H, 0x00, "module 2 compare high byte");
    CHECK_EQ(CCAP2L, 0xFF, "module 2 compare low byte");

    CHECK_EQ(pca_module_get_capture(0), 0xABCD, "module 0 capture read back");
    CHECK_EQ(pca_module_get_capture(1), 0x1234, "module 1 capture read back");
    CHECK_EQ(pca_module_get_capture(2), 0x00FF, "module 2 capture read back");

    /* Token pasting must not cross registers. */
    pca_module_set_compare(2, 0xFFFF);
    CHECK_EQ(CCAP0H, 0xAB, "module 2 write leaves module 0 high untouched");
    CHECK_EQ(CCAP1H, 0x12, "module 2 write leaves module 1 high untouched");
}

/* -------------------------------------------------------------------- pwm */

static void test_pwm(void)
{
    /* EBSn_1:EBSn_0 are PCA_PWMn bits 7:6; PWMn is CCAPMn bit 1.
       00 = 8 bit, 01 = 7 bit, 10 = 6 bit. */
    PCA_PWM0 = 0xFF;
    CCAPM0 = 0x00;
    pca_module_pwm_init(0, PCA_PWM_8BIT);
    CHECK_EQ(PCA_PWM0, 0x3F, "8 bit PWM clears EBS bits");
    CHECK_EQ(CCAPM0, 0x02, "8 bit PWM sets PWMn bit 1");

    PCA_PWM1 = 0xFF;
    CCAPM1 = 0x00;
    pca_module_pwm_init(1, PCA_PWM_7BIT);
    CHECK_EQ(PCA_PWM1, 0x7F, "7 bit PWM sets EBS0 only");
    CHECK_EQ(CCAPM1, 0x02, "7 bit PWM sets PWMn bit 1");

    PCA_PWM2 = 0xFF;
    CCAPM2 = 0x00;
    pca_module_pwm_init(2, PCA_PWM_6BIT);
    CHECK_EQ(PCA_PWM2, 0xBF, "6 bit PWM sets EBS1 only");
    CHECK_EQ(CCAPM2, 0x02, "6 bit PWM sets PWMn bit 1");

    /* Enum encodings match the EBS bit patterns. */
    CHECK_EQ(PCA_PWM_8BIT, 0, "PCA_PWM_8BIT encoding");
    CHECK_EQ(PCA_PWM_7BIT, 1, "PCA_PWM_7BIT encoding");
    CHECK_EQ(PCA_PWM_6BIT, 2, "PCA_PWM_6BIT encoding");

    /* PWM init must not disturb unrelated CCAPMn bits (e.g. ECOM). */
    CCAPM0 = 0x40;
    pca_module_pwm_init(0, PCA_PWM_8BIT);
    CHECK_EQ(CCAPM0 & 0x40, 0x40, "PWM init preserves ECOM");

    /* Duty is written to both CCAPnH and CCAPnL. */
    pca_module_pwm_set_duty(0, 0x80);
    CHECK_EQ(CCAP0H, 0x80, "duty high byte");
    CHECK_EQ(CCAP0L, 0x80, "duty low byte");

    pca_module_pwm_set_duty(1, 0x40);
    CHECK_EQ(CCAP1H, 0x40, "module 1 duty high byte");
    CHECK_EQ(CCAP1L, 0x40, "module 1 duty low byte");

    /* Overflow-only update touches the reload register alone. */
    CCAP2H = 0x00;
    CCAP2L = 0x11;
    pca_module_pwm_set_duty_on_overflow(2, 0x20);
    CHECK_EQ(CCAP2H, 0x20, "overflow update sets high byte");
    CHECK_EQ(CCAP2L, 0x11, "overflow update leaves low byte");

    /* Enable/disable and status. */
    pca_module_pwm_disable(0);
    CHECK_EQ(CCAPM0 & 0x02, 0x00, "pwm disabled clears PWMn");
    CHECK_EQ(is_pca_module_pwm_enabled(0), 0, "pwm status false after disable");
    pca_module_pwm_init(0, PCA_PWM_8BIT);
    CHECK_EQ(is_pca_module_pwm_enabled(0), 1, "pwm status true after init");
}

int main(void)
{
    test_pin_group();
    test_clock_source();
    test_counter();
    test_run_and_idle();
    test_module_bits();
    test_compare_capture();
    test_pwm();

    printf("pca: %d checks, %d failures\n", checks, failures);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
