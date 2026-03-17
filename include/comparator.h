#ifndef STC15_COMPARATORH
#define STC15_COMPARATORH

#include <sys.h>

/**
 * @file comparator.h
 * @defgroup comparator Comparator
 * @details Functions and data structures related to comparator
 */

void comparator_init_async(void);

void comparator_start(void);

void comparator_stop(void);

#endif