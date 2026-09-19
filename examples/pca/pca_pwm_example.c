/**
 * How to generate a PWM signal on the CCP0 pin with PCA module 0.
 *
 * The PCA counter is clocked from SYSclk/12 and module 0 is used as an
 * 8 bit PWM. The duty cycle is changed every 100 ms, so a LED connected
 * to the CCP0 pin fades up and down.
 *
 * Pin group 1 is used, so CCP0 is P1.1. The pin must be configured as
 * push-pull output, otherwise it cannot drive a LED.
 *
 * PWM frequency is SYSclk / (12 * 256) for 8 bit resolution. With the
 * default 24 MHz clock this is about 7.8 kHz.
 */

#include <pca.h>
#include <gpio.h>
#include <delay.h>

// CCP0 is P1.1 in pin group 1. The port is passed to the gpio macros as the
// literal P1 because they paste it into a register name (port ## M1).
#define CCP0_PIN 1

#define DUTY_STEP 1

void main(void)
{
    uint8_t duty = 0;

    // CCP0 is P1.1 in pin group 1, must be push-pull to drive a LED
    pca_set_pin_group(PCA_PIN_GROUP_1);
    pin_push_pull_init(P1, CCP0_PIN);

    // Counter clock is SYSclk/12, module 0 is an 8 bit PWM
    pca_set_clock_source(PCA_CLOCK_SYS_12);
    pca_module_pwm_init(0, PCA_PWM_8BIT);

    // Start with a zero duty cycle
    pca_module_pwm_set_duty(0, 0);

    // Load the counter and start it
    pca_set_counter(0);
    pca_start();

    while (1)
    {
        // CCAP0H is a reload register, the new duty value is applied on
        // the next counter overflow without a glitch on the output
        pca_module_pwm_set_duty_on_overflow(0, duty);

        duty += DUTY_STEP;
        delay_ms(100);
    }
}
