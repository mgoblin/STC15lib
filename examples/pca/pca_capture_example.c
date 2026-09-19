/**
 * How to measure a pulse width with PCA module 0 in 16 bit capture mode.
 *
 * The PCA counter is clocked from SYSclk/12, so one counter tick is 12
 * system clocks. Module 0 captures the counter value on both edges of the
 * CCP0 pin, and the difference between two captures is the pulse width in
 * counter ticks.
 *
 * Pin group 1 is used, so CCP0 is P1.1. The pin is an input here and must
 * be configured as input only.
 *
 * In capture mode CAPPn and/or CAPNn are set and ECOMn is left clear.
 * Setting both CAPP0 and CAPN0 captures on every transition, which makes
 * the handler measure the high time and the low time alternately.
 */

#include <pca.h>
#include <gpio.h>
#include <interrupt.h>

// CCP0 is P1.1 in pin group 1. The port is passed to the gpio macros as the
// literal P1 because they paste it into a register name (port ## M1).
#define CCP0_PIN 1

// Captured counter value of the previous edge
static uint16_t previous_capture = 0;

// Width of the last pulse in PCA counter ticks
static uint16_t pulse_width = 0;

/*
 * PCA interrupt handler.
 *
 * The CCF0 flag is cleared before the capture registers are read, so a new
 * capture cannot be missed while the value is being copied out.
 */
void pca_ISR(void) __interrupt(INTERRUPT_PCA)
{
    if (is_pca_module_flag_set(0))
    {
        pca_clear_module_flag(0);

        uint16_t capture = pca_module_get_capture(0);

        // Unsigned arithmetic handles the counter wrap around
        pulse_width = capture - previous_capture;
        previous_capture = capture;
    }
}

void main(void)
{
    // CCP0 is P1.1 in pin group 1 and is used as an input
    pca_set_pin_group(PCA_PIN_GROUP_1);
    pin_input_only_init(P1, CCP0_PIN);

    // Counter clock is SYSclk/12
    pca_set_clock_source(PCA_CLOCK_SYS_12);

    // Module 0 captures on both edges of CCP0, ECOMn stays clear
    pca_module_enable_capture_positive(0);
    pca_module_enable_capture_negative(0);

    // CCF0 generates a PCA interrupt
    pca_module_enable_interrupt(0);

    // Load the counter and start it
    pca_set_counter(0);
    pca_start();

    enable_mcu_interrupts();

    while (1)
    {
        // pulse_width holds the width of the last pulse in counter ticks
    }
}
