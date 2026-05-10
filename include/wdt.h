#ifndef STC15_WDTH
#define STC15_WDTH

#include <sys.h>
#include <bits.h>

/**
 * @file wdt.h
 * @defgroup wdt Watchdog timer
 * @details Functions and data structures related WDT
 * 
 * WDT - Watchdog timer is purposed for reset MCU on program hang up.
 * 
 * First step is init with scale. Scale determine WDT overflow time.
 * Init WDT assume it not started. 
 * Separate wdt_start() / wdt_stop routines is used for explicitly start and stop WDT.
 * 
 * After wdt_start() call wdt_clear should be periodically called to restart WDT.
 * 
 * If wdt_clear() not called before WDT overflow MCU reset occurs. 
 * 
 * If restart reason is WDT overflow then is_wdt_flag_on() return true.
 * wdt_flag_reset() could be called to clear wdt_flag.
 * 
 * By default WDT is disabled in idle mode. wdt_enable_in_idle() change this.
 * 
 * WDT timings biased by MCU frequency change (frequency divider).
 *  
 * @author Michael Golovanov
 */


/** @name watchdog timer
 *  Watchdog timer functions 
 */
///@{

/**
 * @brief Init WDT
 * @details WDT overflow time = (12 * wdt_scale * 32768) / SysClk
 * 
 * Typical WDT overflow durations for MCU frequency divider 1 shown in the
 * table below
 * 
 * # | PS2, PS1, PS0 | Scale |	Duration, ms
 * - | ------------- | ----- | -------------
 * 1 |	0, 0, 0	     | 2	 | 71,1 ms
 * 2 |	0, 0, 1	     | 4	 | 142,2 ms
 * 3 |	0, 1, 0	     | 8	 | 284,4 ms
 * 4 |	0, 1, 1	     | 16	 | 568,9 ms
 * 5 |	1, 0, 0	     | 32	 | 1137,8 ms (≈1,14 s)
 * 6 |	1, 0, 1	     | 64    | 2275,6 ms (≈2,28 s)
 * 7 |	1, 1, 0	     | 128	 | 4551,2 ms (≈4,55 s)
 * 8 |	1, 1, 1	     | 256	 | 9102,4 ms (≈9,10 s)
 * 
 * @param wdt_scale uint8_t WDT timer scale in range 0..7 
 * 
 * @ingroup wdt
 */
#define wdt_init(wdt_scale)                     \
do {                                            \
    WDT_CONTR = 0;                              \
    WDT_CONTR |= (wdt_scale & 0x07);            \
} while(0)

/**
 * @brief Start WDT
 * @details Call wdt_start after wdt_init call 
 * 
 * @ingroup wdt
 */
#define wdt_start() (bit_set(WDT_CONTR, SBIT5)) 

/**
 * @brief Stop WDT
 * @details Call wdt_stop after wdt_init and wdt_start call 
 * 
 * @ingroup wdt
 */
#define wdt_stop() (bit_clr(WDT_CONTR, CBIT5)) 

/**
 * @brief Get WDT start status
 * @details Call is_wdt_started after wdt_init call 
 * 
 * @return bool - true if WDT started and false if not
 * 
 * @ingroup wdt
 */
#define is_wdt_started() (test_if_bit_set(WDT_CONTR, SBIT5)) 

/**
 * @brief clear WDT to prevent restart
 * @details Call wdt_clear after wdt_start call to prevent WDT reset MCU
 * 
 * @ingroup wdt
 */
#define wdt_clear() (bit_set(WDT_CONTR, SBIT4))

/**
 * @brief Get reset by WDT flag
 * @details WDT reset flag set after restart caused by WDT
 * 
 * @return bool true if MCU reset caused by WDT and false otherwise 
 * 
 * @ingroup wdt
 */
#define is_wdt_flag_on() (test_if_bit_set(WDT_CONTR, SBIT7))

/**
 * @brief Reset WDT flag
 * @details Reset WDT flag to false. 
 * 
 * @ingroup wdt
 */
#define wdt_flag_reset() (bit_clr(WDT_CONTR, CBIT7))

/**
 * @brief Enable WDT in MCU idle mode
 * @details By default WDT in idle mode is disabled.
 * 
 * @ingroup wdt
 */
#define wdt_enable_in_idle() (bit_set(WDT_CONTR, SBIT3))

/**
 * @brief Disable WDT in MCU idle mode
 * @details By default WDT in idle mode is disabled.
 * 
 * @ingroup wdt
 */
#define wdt_disable_in_idle() (bit_clr(WDT_CONTR, CBIT3))

///@}


#endif // STC15_WDTH
