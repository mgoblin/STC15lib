/**
 * How to use PCA module 0 as a 16 bit software timer.
 *
 * The PCA counter is clocked from SYSclk/12. Module 0 compare value is
 * set to 10000, so the CCF0 flag is set every 10000 counter ticks. With
 * the default 24 MHz clock this is every 5 ms.
 *
 * The module interrupt is enabled and the CCF0 flag is cleared in the
 * handler, so the ISR runs every 5 ms. A LED on P1.0 is toggled every
 * 100 interrupts, which is every 500 ms.
 *
 * Note that the PCA counter overflow flag CF and the module flags CCF0,
 * CCF1 and CCF2 share the single PCA interrupt vector.
 */

#include <pca.h>
#include <interrupt.h>

// LED pin
#define LED_PIN P10

// Compare value, CCF0 is set every 10000 counter ticks
#define COMPARE_VALUE 10000

// Number of interrupts in 500 ms
#define INTERRUPTS_PER_HALF_SECOND 100

/*
 * PCA interrupt handler.
 *
 * The CCF0 flag is set on module 0 compare match and must be cleared by
 * software. The counter overflow flag CF is not used here, but if it were
 * enabled it would have to be cleared as well.
 */
void pca_ISR(void) __interrupt(INTERRUPT_PCA)
{
    static uint8_t counter = 0;

    if (is_pca_module_flag_set(0))
    {
        pca_clear_module_flag(0);

        counter++;
        if (counter >= INTERRUPTS_PER_HALF_SECOND)
        {
            counter = 0;
            LED_PIN = !LED_PIN;
        }
    }
}

void main(void)
{
    // Counter clock is SYSclk/12
    pca_set_clock_source(PCA_CLOCK_SYS_12);

    // Module 0 compares the counter with COMPARE_VALUE
    pca_module_set_compare(0, COMPARE_VALUE);
    pca_module_enable_comparator(0);
    pca_module_enable_match(0);

    // CCF0 generates a PCA interrupt
    pca_module_enable_interrupt(0);

    // Load the counter and start it
    pca_set_counter(0);
    pca_start();

    enable_mcu_interrupts();

    while (1)
    {
        // All the work is done in pca_ISR
    }
}
