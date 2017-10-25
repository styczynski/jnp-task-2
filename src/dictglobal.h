/*
 * JNP-ZAD-2
 *
 *  University of Warsaw 2017
 *
 * Contributors:
 *   @wikzan
 *   @styczynski
 */
#include "dict.h"

#ifndef __DICT_GLOBAL__
#define __DICT_GLOBAL__

/*
 * Maximum size of global dictionary.
 * 
 * If this size is exceeded then adding elements has no effect
 * on the global dictionary.
 */
__attribute__((unused)) static unsigned long MAX_GLOBAL_DICT_SIZE = 42;
 
 
/*
 * Returns the id of global dictionary.
 *
 * Global dictionary is unremovable.
 * dict_remove on it has no effects.
 * 
 */
unsigned long dict_global();

#endif // __DICT_GLOBAL__