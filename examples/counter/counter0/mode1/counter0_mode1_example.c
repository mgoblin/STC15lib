/** 
 * @file counter0_mode1_example.c
 * 
 * How to use counter0 in mode1.
 * 
 * Program counts from 65530 to 65535 (5 times). 
 * Counter is drived by T0 pin change state in a main function.
 * On T0 pin change from 1 to 0 counter is incremented.
 * On each T0 pin change LED is toggled.
 * 
 * LED is blinking 5 times and counter is stopped. 
 * On each T0 pin change counter value printed to UART.
 * 
 * @author Mike Golovanov
 */
#include <counter0_mode1.h>
#include <uart.h>
#include <delay.h>

#include <stdio.h>

/// @brief Counter0 initial value. Counts is 65535 - initial value
#define COUNTER0_INITIAL_VALUE 65530 // 5 counts

/// @brief LED pin
#define LED_PIN P10
/// @brief LED state OFF
#define LED_OFF 1
/// @brief LED state ON
#define LED_ON 0

/// @brief Counter0 interrupt service routine
void counter0ISR() __interrupt(1)
{
    printf_tiny("Counter is full and counter will be stoped\r\n");

    counter0_mode1_stop();
}

/// @brief main function
void main()
{
    uart1_init(9600);

    LED_PIN = LED_OFF;

    // Initialize counter0 with mode1    
    counter0_mode1_init();

    // Start counter0
    counter0_mode1_start(COUNTER0_INITIAL_VALUE);

    while (1)
    {
        if(is_counter0_mode1_started())
        {
            // Toggle T0 pin change state
            T0 = !T0;

            // Toggle LED
            LED_PIN = !LED_PIN;
            
            // Print counter value. Counter value is changed  
            // only on T0 pin change from 1 to 0
            printf_tiny("Counter value is %u and T0 is %d\r\n", 
                counter0_mode1_get_value(), T0);

            delay_ms(1000);    
        } else
        {
            // After counter0 stopped LED should be OFF
            LED_PIN = LED_OFF;
        }
    }
    
}