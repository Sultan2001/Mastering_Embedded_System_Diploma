/*
 * Platform_Types.h
 *
 *  Created on: Oct 6, 2023
 *      Author: mohamedsultan
 */

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

typedef unsigned int        uint_32;
typedef unsigned short      uint_16;
typedef unsigned char       uint_8;
typedef unsigned long long  uint_64;


typedef volatile unsigned int        vuint_32;
typedef volatile unsigned short      vuint_16;
typedef volatile unsigned char       vuint_8;
typedef volatile unsigned long long  vuint_64;


typedef signed int   sint_32;
typedef signed short sint_16;
typedef signed char  sint_8;


typedef volatile signed int   vsint_32;
typedef volatile signed short vsint_16;
typedef volatile signed char  vsint_8;

enum Polling_mechism
{
	Enable,
	Disable
};


#endif /* PLATFORM_TYPES_H_ */
