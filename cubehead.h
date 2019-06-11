#ifndef __CUBEHEAD_H
#define __CUBEHEAD_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>

	//put defines for compiling with arduino here

	#define CUBE_WIDTH 5
	#define CHARMAP_COMPRESS
	//#define DIGITALWRITE_FAST
	//#define CUBE_CURFRAME
	#define PATTERN_KILLFLAG
	#define USE_PROGMEM
	//#define USE_SPI_SHIFTOUT
#endif

#ifndef CUBE_WIDTH
	#define CUBE_WIDTH 5
	#warning "Cube width not defined, defaulting to 5..."
#endif

#ifndef CUBE_WIDTH
	#error "Cube width is not defined"
#endif

#if CUBE_WIDTH > 255
	#error "Maximum cube width is 255"
#endif

#if CUBE_WIDTH < 3
	#error "Minimum cube width is 3"
#endif

#define CUBE_AREA (CUBE_WIDTH * CUBE_WIDTH)
#define CUBE_VOLUME (CUBE_WIDTH * CUBE_AREA)

// https://stackoverflow.com/a/5504336
#define PROTECT(...) __VA_ARGS__

#ifdef CHARMAP_COMPRESS
	#define CHARMAP_DATA(U, C) C
#else
	#define CHARMAP_DATA(U, C) U
#endif

#ifdef USE_PROGMEM
	#define PROGMEM_ENABLED PROGMEM
#else
	#define PROGMEM_ENABLED
#endif

#endif //ndef __CUBEHEAD_H
