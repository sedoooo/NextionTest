#ifndef UTITLITIES_H
#define UTITLITIES_H

#include <stdint.h>

/*******************************************************************************
 * TYPES
 *******************************************************************************/
#if 0
typedef short int8_t;
typedef unsigned short uint8_t;
typedef int int16_t;
typedef unsigned int uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
#endif
/*******************************************************************************
 * MACROS
 *******************************************************************************/
#define ClearArray(arr,l) memset(arr, 0, l)
#define ClearString(str) memset(str, 0, strlen(str))
#define ArrayCopy(d, s, l) \
    ClearArray(d,l);         \
    memcpy(d, s, l)
#define StringCopy(d, s) \
    ClearString(d);      \
    memcpy(d, s, strlen(s))
#define StringAppend(d, s) strcat(d, s)
/*******************************************************************************
 * FUNCTIONS
 *******************************************************************************/
uint8_t ArrayLength(char *arr);
char *utoac(char *str, unsigned int value, int radix);
#endif
