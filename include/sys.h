#ifndef STC15_SYSH
#define STC15_SYSH

/**
 * @file sys.h
 * @details System constants. 
 * @author Michael Golovanov
 */

#include <STC15Fxx.h>

/**
 * CPU frequency
 */
//#define MAIN_Fosc 22118400L   //Define the clock
//#define MAIN_Fosc 12000000L   //Define the clock
#define MAIN_Fosc 11059200UL    //Define the clock
//#define MAIN_Fosc 5529600L    //Define the clock
//#define MAIN_Fosc 24000000L   //Define the clock

/** CPU frequency high part */
#define MAIN_FoscH 11059
/** CPU frequency low part */
#define MAIN_FoscL 200

#endif 