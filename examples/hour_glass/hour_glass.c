#include <pin.h>

#include <delay.h>


#define HIGH 1
#define LOW 0

void f_delay_ms(uint16_t ms)
{
    delay_ms(ms);
}

void led_on()
{
    pin_push_pull_init(P3, 0); // put P3.0 in output strong mode
    pin_push_pull_init(P1, 0); // put P1.0 in output strong mode 

    // LED on 
    P30 = HIGH; 
    P10 = LOW;
}

void led_off()
{
    pin_input_only_init(P3, 0); // put P3.0 in high impedance mode
    pin_input_only_init(P1, 0); // put P1.0 in high impedance mode
}

void main()
{
    port_mode_input_only_init(P1);
    port_mode_input_only_init(P3);

    while (1)
    {
        led_on();
        f_delay_ms(15);
        led_off();
        f_delay_ms(15);
    }
}