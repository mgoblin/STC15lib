/**
 * This example shows how to use the wakeup timer functionality to periodically
 * wake up the microcontroller from power-down mode at regular intervals.
 * 
 * The example configures the wakeup timer to wake up every 3 seconds (defined
 * by LED_ON_SECONDS). In the main loop, the MCU enters power-down mode, which
 * significantly reduces power consumption. After the specified time interval,
 * the wakeup timer automatically wakes up the MCU, and the program toggles
 * an LED before returning to power-down mode.
 * 
 * This demonstrates a common power-saving technique where the microcontroller
 * spends most of its time in low-power mode and only wakes up periodically
 * to perform tasks.
 * 
 * Hardware setup:
 * - LED connected to P1.0 pin
 * 
 * @see power_management.h - Header file containing power management functions
 * @see wakeup_timer_init_seconds() - Function used to configure wakeup timer in seconds
 * @see power_down() - Function that puts MCU into power-down mode
 * 
 */
#include <power_management.h>

#define LED P10
#define LED_ON_SECONDS 3

void main(void)
{
    // Timer is wakeup MCU every 3 seconds
    wakeup_timer_init_seconds(LED_ON_SECONDS);
    
    while (1)
    {
        // Going to power down mode until wakeup timer
        power_down();
        // Flip LED state
        LED = !LED;
    }
}