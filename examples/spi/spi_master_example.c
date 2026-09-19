/** How to transfer data over SPI in master mode
 *
 * Connect the MISO (P1.4) pin to the MOSI (P1.3) pin, so every byte sent is
 * received back. The received byte should be equal to the sent one.
 */

#include <spi.h>

#include <stdio.h>
#include <uart.h>
#include <delay.h>

void main(void)
{
    uint8_t tx = 0;
    uint8_t rx;

    uart1_init(9600);

    // Init SPI as a master on pin group 1 (SS P1.2, MOSI P1.3, MISO P1.4,
    // SCLK P1.5), mode 0, SYSclk/16, MSB first
    spi_init_master(SPI_PIN_GROUP_1, SPI_MODE_0, SPI_CLOCK_DIV_16, false);

    while (1)
    {
        // In mode 0 the SS pin is not ignored, so the slave has to be
        // selected before every byte and deselected after it
        spi_ss_clr(SPI_PIN_GROUP_1);
        spi_transfer_sync(&rx, tx);
        spi_ss_set(SPI_PIN_GROUP_1);

        printf_tiny("Sent %x, got %x\r\n", tx, rx);

        tx++;
        delay_ms(1000);
    }
}
