#ifndef STC15_SPIH
#define STC15_SPIH

/**
 * @file spi.h
 *
 * @defgroup spi SPI
 *
 * @details Functions and data structures related to SPI module
 *
 * SPI - Serial Peripheral Interface. It is a full duplex synchronous serial
 * link with a master and one or more slaves. Four wires are used:
 * SS (slave select), MOSI (master output, slave input),
 * MISO (master input, slave output) and SCLK (serial clock).
 *
 * The SPI module could work in master or slave mode. In master mode the
 * clock rate is selected from the CPU clock (SYSclk) with one of the four
 * available dividers. In slave mode the module is clocked by the master and
 * the clock rate setting is ignored.
 *
 * Four clock phase and polarity combinations (modes 0..3) and either data
 * order (MSB or LSB first) are supported.
 *
 * Transfers could be done in sync mode, which blocks until the transfer is
 * finished, or in async mode. In async mode the SPI transfer complete event
 * generates an interrupt. Before async transfers mcu interrupts and the SPI
 * interrupt should be enabled by calling enable_spi_interrupt() from
 * interrupt.h.
 *
 * Pin mapping is selected with spi_set_pin_group(). Three pin groups are
 * available and the group selection is stored in the P_SW1 register:
 *
 * | Group | SS    | MOSI  | MISO  | SCLK  |
 * |-------|-------|-------|-------|-------|
 * | 1     | P1.2  | P1.3  | P1.4  | P1.5  |
 * | 2     | P2.4  | P2.3  | P2.2  | P2.1  |
 * | 3     | P5.4  | P4.0  | P4.1  | P4.3  |
 *
 * Note that not every pin group is available on every MCU series and package.
 * For example the STC15W408AS exposes group 1 on every package, group 2 only
 * on 28 pin packages and has no P4 port pins bonded out for group 3 at all.
 *
 * @author Michael Golovanov
 */

#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>
#include <gpio.h>

/**
 * @brief SPCTL register SSIG (SS ignore) bit position.
 * @details If SSIG=1, MSTR decides whether the device is a master or a slave.
 * If SSIG=0, the SS pin decides it. Note that if SSIG=1, CPHA must not be 0,
 * otherwise the operation is undefined.
 */
#define SPI_SSIG_BIT 7
/** @brief SPCTL register SPEN (SPI enable) bit position */
#define SPI_SPEN_BIT 6
/** @brief SPCTL register DORD (data order) bit position */
#define SPI_DORD_BIT 5
/** @brief SPCTL register MSTR (master mode select) bit position */
#define SPI_MSTR_BIT 4
/** @brief SPCTL register CPOL (SPI clock polarity) bit position */
#define SPI_CPOL_BIT 3
/** @brief SPCTL register CPHA (SPI clock phase) bit position */
#define SPI_CPHA_BIT 2
/** @brief SPCTL register SPR1 (clock rate select) bit position */
#define SPI_SPR1_BIT 1
/** @brief SPCTL register SPR0 (clock rate select) bit position */
#define SPI_SPR0_BIT 0

/** @brief SPCTL register SSIG bit mask */
#define SPI_SSIG_MSK 0x80
/** @brief SPCTL register SPEN bit mask */
#define SPI_SPEN_MSK 0x40
/** @brief SPCTL register DORD bit mask */
#define SPI_DORD_MSK 0x20
/** @brief SPCTL register MSTR bit mask */
#define SPI_MSTR_MSK 0x10
/** @brief SPCTL register CPOL bit mask */
#define SPI_CPOL_MSK 0x08
/** @brief SPCTL register CPHA bit mask */
#define SPI_CPHA_MSK 0x04
/** @brief SPCTL register SPR (clock rate select) bits mask */
#define SPI_SPR_MSK 0x03

/** @brief SPSTAT register SPIF (transfer complete) bit position */
#define SPI_SPIF_BIT 7
/** @brief SPSTAT register WCOL (write collision) bit position */
#define SPI_WCOL_BIT 6

/** @brief SPSTAT register SPIF bit mask */
#define SPI_SPIF_MSK 0x80
/** @brief SPSTAT register WCOL bit mask */
#define SPI_WCOL_MSK 0x40
/** @brief SPSTAT register flags mask. Both flags are cleared by writing 1 */
#define SPI_SPSTAT_CLEAR_MSK (SPI_SPIF_MSK | SPI_WCOL_MSK)

/** @brief P_SW1 register SPI_S0 (SPI pin group select) bit position */
#define SPI_S0_BIT 2
/** @brief P_SW1 register SPI_S0 (SPI pin group select) bit mask */
#define SPI_S0_MSK 0x04
/** @brief P_SW1 register SPI_S1 (SPI pin group select) bit mask */
#define SPI_S1_MSK 0x08
/** @brief P_SW1 register SPI pin group select bits mask */
#define SPI_SW_MSK (uint8_t)(~(SPI_S0_MSK | SPI_S1_MSK))

/**
 * @brief SPI clock rate
 *
 * @details describes possible SPI clock dividers. The SPI clock is derived
 * from the CPU clock (SYSclk). Used in master mode only, in slave mode the
 * module is clocked by an external master.
 *
 * @ingroup spi
 */
typedef enum
{
    /** SYSclk / 4 */
    SPI_CLOCK_DIV_4 = 0b00000000,
    /** SYSclk / 16 */
    SPI_CLOCK_DIV_16 = 0b00000001,
    /** SYSclk / 64, used after MCU power on */
    SPI_CLOCK_DIV_64 = 0b00000010,
    /** SYSclk / 128 */
    SPI_CLOCK_DIV_128 = 0b00000011
} spi_clock_t;

/**
 * @brief SPI mode
 *
 * @details describes all four combinations of the CPOL (clock polarity) and
 * CPHA (clock phase) bits. The current mode could be read back with
 * spi_get_mode().
 *
 * Note that in modes with CPHA=0 (SPI_MODE_0 and SPI_MODE_2) the SS pin is
 * not ignored (SSIG=0), so it has to be pulled low with spi_ss_clr() before
 * every byte transfer and released with spi_ss_set() after it.
 *
 * @ingroup spi
 */
typedef enum
{
    /** CPOL=0, CPHA=0. Clock is low when idle, data is sampled on the leading edge */
    SPI_MODE_0 = 0b00000000,
    /** CPOL=0, CPHA=1. Clock is low when idle, data is changed on the leading edge */
    SPI_MODE_1 = 0b00000100,
    /** CPOL=1, CPHA=0. Clock is high when idle, data is sampled on the leading edge */
    SPI_MODE_2 = 0b00001000,
    /** CPOL=1, CPHA=1. Clock is high when idle, data is changed on the leading edge */
    SPI_MODE_3 = 0b00001100
} spi_mode_t;

/**
 * @brief SPI pin group
 *
 * @details describes possible SS/MOSI/MISO/SCLK pin mapping variants.
 * Group selection is done with spi_set_pin_group().
 *
 * Note that not every pin group is available on every MCU series and package.
 * For example the STC15W408AS exposes group 1 on every package, group 2 only
 * on 28 pin packages and has no P4 port pins bonded out for group 3 at all.
 *
 * @ingroup spi
 */
typedef enum
{
    /** SS on P1.2, MOSI on P1.3, MISO on P1.4, SCLK on P1.5. Default after power on */
    SPI_PIN_GROUP_1 = 0,
    /** SS_2 on P2.4, MOSI_2 on P2.3, MISO_2 on P2.2, SCLK_2 on P2.1 */
    SPI_PIN_GROUP_2 = 1,
    /** SS_3 on P5.4, MOSI_3 on P4.0, MISO_3 on P4.1, SCLK_3 on P4.3 */
    SPI_PIN_GROUP_3 = 2
} spi_pin_group_t;

/**
 * @brief Configure the SPI pins of pin group 1 for master mode
 *
 * @details SS on P1.2 as push-pull output and kept high, MOSI on P1.3 as
 * push-pull output, MISO on P1.4 as input only, SCLK on P1.5 as push-pull
 * output.
 *
 * Used by spi_init_master_pins(). Normally there is no need to call it
 * directly.
 *
 * @ingroup spi
 */
#define spi_init_master_pins_SPI_PIN_GROUP_1()                               \
do {                                                                         \
    /* SS on P1.2 as push-pull output, kept high */                          \
    pin_push_pull_init(P1, 2);                                               \
    bit_set(P1, SBIT2);                                                      \
    /* MOSI on P1.3 as push-pull output */                                   \
    pin_push_pull_init(P1, 3);                                               \
    /* MISO on P1.4 as input only */                                         \
    pin_input_only_init(P1, 4);                                              \
    /* SCLK on P1.5 as push-pull output */                                   \
    pin_push_pull_init(P1, 5);                                               \
} while(0)

/**
 * @brief Configure the SPI pins of pin group 2 for master mode
 *
 * @details SS_2 on P2.4 as push-pull output and kept high, MOSI_2 on P2.3 as
 * push-pull output, MISO_2 on P2.2 as input only, SCLK_2 on P2.1 as push-pull
 * output.
 *
 * Used by spi_init_master_pins(). Normally there is no need to call it
 * directly.
 *
 * @ingroup spi
 */
#define spi_init_master_pins_SPI_PIN_GROUP_2()                               \
do {                                                                         \
    /* SS_2 on P2.4 as push-pull output, kept high */                        \
    pin_push_pull_init(P2, 4);                                               \
    bit_set(P2, SBIT4);                                                      \
    /* MOSI_2 on P2.3 as push-pull output */                                 \
    pin_push_pull_init(P2, 3);                                               \
    /* MISO_2 on P2.2 as input only */                                       \
    pin_input_only_init(P2, 2);                                              \
    /* SCLK_2 on P2.1 as push-pull output */                                 \
    pin_push_pull_init(P2, 1);                                               \
} while(0)

/**
 * @brief Configure the SPI pins of pin group 3 for master mode
 *
 * @details SS_3 on P5.4 as push-pull output and kept high, MOSI_3 on P4.0 as
 * push-pull output, MISO_3 on P4.1 as input only, SCLK_3 on P4.3 as push-pull
 * output.
 *
 * Used by spi_init_master_pins(). Normally there is no need to call it
 * directly.
 *
 * @note Pin group 3 is not available on the STC15W401AS series, which has no
 * P4 port pins bonded out.
 *
 * @ingroup spi
 */
#define spi_init_master_pins_SPI_PIN_GROUP_3()                               \
do {                                                                         \
    /* SS_3 on P5.4 as push-pull output, kept high */                        \
    pin_push_pull_init(P5, 4);                                               \
    bit_set(P5, SBIT4);                                                      \
    /* MOSI_3 on P4.0 as push-pull output */                                 \
    pin_push_pull_init(P4, 0);                                               \
    /* MISO_3 on P4.1 as input only */                                       \
    pin_input_only_init(P4, 1);                                              \
    /* SCLK_3 on P4.3 as push-pull output */                                 \
    pin_push_pull_init(P4, 3);                                               \
} while(0)

/**
 * @brief Configure the SPI pins of pin group 1 for slave mode
 *
 * @details SS on P1.2 as input only, MOSI on P1.3 as input only, MISO on
 * P1.4 as push-pull output, SCLK on P1.5 as input only.
 *
 * Used by spi_init_slave_pins(). Normally there is no need to call it
 * directly.
 *
 * @ingroup spi
 */
#define spi_init_slave_pins_SPI_PIN_GROUP_1()                                \
do {                                                                         \
    /* SS on P1.2 as input only */                                           \
    pin_input_only_init(P1, 2);                                              \
    /* MOSI on P1.3 as input only */                                         \
    pin_input_only_init(P1, 3);                                              \
    /* MISO on P1.4 as push-pull output */                                   \
    pin_push_pull_init(P1, 4);                                               \
    /* SCLK on P1.5 as input only */                                         \
    pin_input_only_init(P1, 5);                                              \
} while(0)

/**
 * @brief Configure the SPI pins of pin group 2 for slave mode
 *
 * @details SS_2 on P2.4 as input only, MOSI_2 on P2.3 as input only, MISO_2
 * on P2.2 as push-pull output, SCLK_2 on P2.1 as input only.
 *
 * Used by spi_init_slave_pins(). Normally there is no need to call it
 * directly.
 *
 * @ingroup spi
 */
#define spi_init_slave_pins_SPI_PIN_GROUP_2()                                \
do {                                                                         \
    /* SS_2 on P2.4 as input only */                                         \
    pin_input_only_init(P2, 4);                                              \
    /* MOSI_2 on P2.3 as input only */                                       \
    pin_input_only_init(P2, 3);                                              \
    /* MISO_2 on P2.2 as push-pull output */                                 \
    pin_push_pull_init(P2, 2);                                               \
    /* SCLK_2 on P2.1 as input only */                                       \
    pin_input_only_init(P2, 1);                                              \
} while(0)

/**
 * @brief Configure the SPI pins of pin group 3 for slave mode
 *
 * @details SS_3 on P5.4 as input only, MOSI_3 on P4.0 as input only, MISO_3
 * on P4.1 as push-pull output, SCLK_3 on P4.3 as input only.
 *
 * Used by spi_init_slave_pins(). Normally there is no need to call it
 * directly.
 *
 * @note Pin group 3 is not available on the STC15W401AS series, which has no
 * P4 port pins bonded out.
 *
 * @ingroup spi
 */
#define spi_init_slave_pins_SPI_PIN_GROUP_3()                                \
do {                                                                         \
    /* SS_3 on P5.4 as input only */                                         \
    pin_input_only_init(P5, 4);                                              \
    /* MOSI_3 on P4.0 as input only */                                       \
    pin_input_only_init(P4, 0);                                              \
    /* MISO_3 on P4.1 as push-pull output */                                 \
    pin_push_pull_init(P4, 1);                                               \
    /* SCLK_3 on P4.3 as input only */                                       \
    pin_input_only_init(P4, 3);                                              \
} while(0)

/**
 * @brief Pull the SS pin of pin group 1 low
 *
 * @details SS on P1.2 is configured as a push-pull output by
 * spi_init_master_pins_SPI_PIN_GROUP_1()
 *
 * @ingroup spi
 */
#define spi_ss_clr_SPI_PIN_GROUP_1() (bit_clr(P1, CBIT2))

/**
 * @brief Pull the SS pin of pin group 1 high
 *
 * @ingroup spi
 */
#define spi_ss_set_SPI_PIN_GROUP_1() (bit_set(P1, SBIT2))

/**
 * @brief Pull the SS pin of pin group 2 low
 *
 * @details SS_2 on P2.4 is configured as a push-pull output by
 * spi_init_master_pins_SPI_PIN_GROUP_2()
 *
 * @ingroup spi
 */
#define spi_ss_clr_SPI_PIN_GROUP_2() (bit_clr(P2, CBIT4))

/**
 * @brief Pull the SS pin of pin group 2 high
 *
 * @ingroup spi
 */
#define spi_ss_set_SPI_PIN_GROUP_2() (bit_set(P2, SBIT4))

/**
 * @brief Pull the SS pin of pin group 3 low
 *
 * @details SS_3 on P5.4 is configured as a push-pull output by
 * spi_init_master_pins_SPI_PIN_GROUP_3()
 *
 * @note Pin group 3 is not available on the STC15W401AS series.
 *
 * @ingroup spi
 */
#define spi_ss_clr_SPI_PIN_GROUP_3() (bit_clr(P5, CBIT4))

/**
 * @brief Pull the SS pin of pin group 3 high
 *
 * @ingroup spi
 */
#define spi_ss_set_SPI_PIN_GROUP_3() (bit_set(P5, SBIT4))

/** @name init
 *  SPI initialization routines
 */
///@{

/**
 * @brief Configure the SPI pins for master mode
 *
 * @details Configures the SS, MOSI and SCLK pins as push-pull outputs and
 * the MISO pin as input only for the given pin group. The SS pin is kept
 * high, so an external slave stays deselected and the SPI is not switched
 * to slave mode by the SS pin.
 *
 * @param group spi_pin_group_t pin group to use. Must be a compile time
 * constant, for example SPI_PIN_GROUP_1
 *
 * @ingroup spi
 */
#define spi_init_master_pins(group) spi_init_master_pins_##group()

/**
 * @brief Configure the SPI pins for slave mode
 *
 * @details Configures the SS, MOSI and SCLK pins as input only and the MISO
 * pin as push-pull output for the given pin group.
 *
 * @param group spi_pin_group_t pin group to use. Must be a compile time
 * constant, for example SPI_PIN_GROUP_1
 *
 * @ingroup spi
 */
#define spi_init_slave_pins(group) spi_init_slave_pins_##group()

/**
 * @brief SPI initialization in master mode
 *
 * @details Selects the pin group with spi_set_pin_group(), configures the
 * SS, MOSI, MISO and SCLK pins and writes the SPCTL register with the SPI
 * enable, master mode, clock divider, mode and data order bits.
 *
 * The SS pin is configured as an output and kept high. In modes with CPHA=0
 * (SPI_MODE_0 and SPI_MODE_2) the SS pin is not ignored (SSIG=0), so it has
 * to be pulled low with spi_ss_clr() before every byte transfer and released
 * with spi_ss_set() after it. In modes with CPHA=1 the SS pin is ignored
 * (SSIG=1) and could be left high all the time.
 *
 * @param group spi_pin_group_t pin group to use. Must be a compile time
 * constant, for example SPI_PIN_GROUP_1
 * @param mode spi_mode_t SPI mode (CPOL and CPHA combination)
 * @param clock spi_clock_t SPI clock divider, SPI clock is derived from SYSclk
 * @param lsb_first bool data order, true transmits LSB first, false MSB first
 *
 * @ingroup spi
 */
#define spi_init_master(group, mode, clock, lsb_first)                       \
do {                                                                         \
    /* Select the SS/MOSI/MISO/SCLK pin group */                             \
    spi_set_pin_group(group);                                                \
    /* Configure the SS/MOSI/MISO/SCLK pins */                               \
    spi_init_master_pins(group);                                             \
    /* Enable SPI as a master with the given mode, clock and data order */   \
    SPCTL = SPI_SPEN_MSK | SPI_MSTR_MSK | (mode) | (clock) |                 \
        ((lsb_first) ? SPI_DORD_MSK : 0) |                                   \
        (((mode) & SPI_CPHA_MSK) ? SPI_SSIG_MSK : 0);                        \
} while(0)

/**
 * @brief SPI initialization in slave mode
 *
 * @details Selects the pin group with spi_set_pin_group(), configures the
 * SS, MOSI, MISO and SCLK pins and writes the SPCTL register with the SPI
 * enable, mode and data order bits. The SS pin always selects the device
 * (SSIG=0) and the SPI is clocked by an external master, so the clock rate
 * setting is not used.
 *
 * @param group spi_pin_group_t pin group to use. Must be a compile time
 * constant, for example SPI_PIN_GROUP_1
 * @param mode spi_mode_t SPI mode (CPOL and CPHA combination)
 * @param lsb_first bool data order, true transmits LSB first, false MSB first
 *
 * @ingroup spi
 */
#define spi_init_slave(group, mode, lsb_first)                               \
do {                                                                         \
    /* Select the SS/MOSI/MISO/SCLK pin group */                             \
    spi_set_pin_group(group);                                                \
    /* Configure the SS/MOSI/MISO/SCLK pins */                               \
    spi_init_slave_pins(group);                                              \
    /* Enable SPI as a slave with the given mode and data order */           \
    SPCTL = SPI_SPEN_MSK | (mode) | ((lsb_first) ? SPI_DORD_MSK : 0);        \
} while(0)

/**
 * @brief Deinitialize the SPI module
 *
 * @details Disables the SPI interface by clearing the SPEN bit and clears
 * the transfer complete and write collision flags. After that the SPI pins
 * function as normal I/O port pins, but their configured modes (push-pull
 * output, input only) are kept.
 *
 * @ingroup spi
 */
#define spi_destroy(void)                                                    \
do {                                                                         \
    /* Disable the SPI interface */                                          \
    SPCTL = 0;                                                               \
    /* Clear the SPIF and WCOL flags */                                      \
    bit_set(SPSTAT, SPI_SPSTAT_CLEAR_MSK);                                   \
} while(0)

///@}

/** @name pin group
 *  SPI pin mapping functions
 */
///@{

/**
 * @brief Set the SS/MOSI/MISO/SCLK pin group
 * @details Select which pins are used as SS, MOSI, MISO and SCLK.
 * Pins are selected with the P_SW1 register SPI_S1 and SPI_S0 bits.
 *
 * By default (after MCU power on) pin group 1 is used.
 *
 * @param group spi_pin_group_t pin group to use
 *
 * @ingroup spi
 */
#define spi_set_pin_group(group)                                             \
do {                                                                         \
    bit_clr(P_SW1, SPI_SW_MSK);                                              \
    bit_set(P_SW1, (uint8_t)((group) << SPI_S0_BIT));                        \
} while(0)

/**
 * @brief Get the SS/MOSI/MISO/SCLK pin group
 *
 * @return spi_pin_group_t current pin group
 *
 * @ingroup spi
 */
#define spi_get_pin_group() ((spi_pin_group_t)(bit_shift_right(get_reg(P_SW1, (SPI_S0_MSK | SPI_S1_MSK)), SPI_S0_BIT)))

///@}

/** @name slave select
 *  SPI slave select (SS) pin handling in master mode
 */
///@{

/**
 * @brief Select an external slave
 *
 * @details Pulls the SS pin low. The SS pin is configured as a push-pull
 * output by spi_init_master().
 *
 * @param group spi_pin_group_t pin group in use. Must be the literal enum
 * constant, for example SPI_PIN_GROUP_1, not a variable: the pin group is
 * selected at compile time by token pasting, so unlike
 * spi_set_pin_group() this routine cannot take a runtime value
 *
 * @ingroup spi
 */
#define spi_ss_clr(group) spi_ss_clr_##group()

/**
 * @brief Deselect an external slave
 *
 * @details Pulls the SS pin high. The SS pin is configured as a push-pull
 * output by spi_init_master().
 *
 * @param group spi_pin_group_t pin group in use. Must be the literal enum
 * constant, for example SPI_PIN_GROUP_1, not a variable: the pin group is
 * selected at compile time by token pasting, so unlike
 * spi_set_pin_group() this routine cannot take a runtime value
 *
 * @ingroup spi
 */
#define spi_ss_set(group) spi_ss_set_##group()

///@}

/** @name sync
 *  SPI synchronous transfer functions
 */
///@{

/**
 * @brief Write a byte over SPI
 *
 * @details Clears the status flags, writes a byte into the SPI data register,
 * which starts the transfer, and blocks until the transfer is finished.
 * The received byte is discarded.
 *
 * @param data uint8_t byte to transmit
 *
 * @ingroup spi
 */
#define spi_write_sync(data)                                                 \
do {                                                                         \
    /* Clear the SPIF and WCOL flags */                                      \
    bit_set(SPSTAT, SPI_SPSTAT_CLEAR_MSK);                                   \
    /* Writing the data register starts the transfer */                      \
    SPDAT = (data);                                                          \
    /* Wait until the transfer is finished */                                \
    while (test_if_bit_cleared(SPSTAT, SPI_SPIF_MSK));                       \
    /* Clear the SPIF and WCOL flags */                                      \
    bit_set(SPSTAT, SPI_SPSTAT_CLEAR_MSK);                                   \
} while(0)

/**
 * @brief Transfer a byte over SPI
 *
 * @details Writes a byte into the SPI data register, which starts the
 * transfer, blocks until the transfer is finished and stores the received
 * byte.
 *
 * @param value uint8_t* received byte
 * @param data uint8_t byte to transmit
 *
 * @ingroup spi
 */
#define spi_transfer_sync(value, data)                                       \
do {                                                                         \
    spi_write_sync(data);                                                    \
    /* Store the received byte */                                            \
    *(value) = SPDAT;                                                        \
} while(0)

///@}

/** @name async
 *  SPI asynchronous transfer functions
 */
///@{

/**
 * @brief Start an asynchronous SPI transfer
 *
 * @details Clears the status flags and writes a byte into the SPI data
 * register, which starts the transfer. The program is not blocked after
 * that. When the transfer is finished the MCU generates an SPI interrupt.
 *
 * @note MCU interrupts and the SPI interrupt should be enabled before async
 * transfers by calling enable_spi_interrupt() from interrupt.h
 *
 * @param data uint8_t byte to transmit
 *
 * @ingroup spi
 */
#define spi_async_transfer_start(data)                                       \
do {                                                                         \
    /* Clear the SPIF and WCOL flags */                                      \
    bit_set(SPSTAT, SPI_SPSTAT_CLEAR_MSK);                                   \
    /* Writing the data register starts the transfer */                      \
    SPDAT = (data);                                                          \
} while(0)

/**
 * @brief Get the SPI asynchronous transfer status
 *
 * @return bool true if the transfer is finished, otherwise false
 *
 * @ingroup spi
 */
#define is_spi_async_transfer_complete() (test_if_bit_set(SPSTAT, SPI_SPIF_MSK))

/**
 * @brief Clear the SPI transfer complete and write collision flags
 *
 * @note This routine is supposed to be called inside the SPI interrupt
 * handler
 *
 * @ingroup spi
 */
#define spi_async_transfer_finish() (bit_set(SPSTAT, SPI_SPSTAT_CLEAR_MSK))

/**
 * @brief Get the byte received in the asynchronous transfer
 *
 * @details The SPI data register is double buffered, so it holds the byte
 * received during the last completed transfer.
 *
 * This routine is supposed to be used inside the SPI interrupt handler.
 * Typically spi_async_transfer_finish() is called after it to clear the
 * transfer complete flag.
 *
 * @return uint8_t received byte
 *
 * @ingroup spi
 */
#define spi_async_get_result() (SPDAT)

///@}

/** @name status
 *  SPI state functions
 */
///@{

/**
 * @brief Get the SPI enable status
 *
 * @return bool true if the SPI interface is enabled, otherwise false
 *
 * @ingroup spi
 */
#define is_spi_enabled() (test_if_bit_set(SPCTL, SPI_SPEN_MSK))

/**
 * @brief Get the SPI master/slave mode status
 *
 * @return bool true if the SPI works in master mode, otherwise false
 *
 * @ingroup spi
 */
#define is_spi_master() (test_if_bit_set(SPCTL, SPI_MSTR_MSK))

/**
 * @brief Get the SPI write collision status
 *
 * @details The WCOL flag is set if the SPI data register is written while a
 * transfer is still in progress. The flag is cleared by
 * spi_async_transfer_finish() or by spi_write_sync().
 *
 * @return bool true if a write collision happened, otherwise false
 *
 * @ingroup spi
 */
#define is_spi_write_collision() (test_if_bit_set(SPSTAT, SPI_WCOL_MSK))

/**
 * @brief Get the SPI mode
 *
 * @return spi_mode_t current CPOL and CPHA combination
 *
 * @ingroup spi
 */
#define spi_get_mode() ((spi_mode_t)get_reg(SPCTL, (SPI_CPOL_MSK | SPI_CPHA_MSK)))

/**
 * @brief Get the SPI clock divider
 *
 * @return spi_clock_t current SPI clock divider
 *
 * @ingroup spi
 */
#define spi_get_clock() ((spi_clock_t)get_reg(SPCTL, SPI_SPR_MSK))

///@}

#endif
