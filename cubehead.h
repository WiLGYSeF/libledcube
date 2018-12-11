#ifndef __CUBEHEAD_H
#define __CUBEHEAD_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>

	#define PATTERN_KILLFLAG
	#define CUBE_WIDTH 5
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
	#warning "Minimum cube width is 3"
#endif

#define CUBE_AREA (CUBE_WIDTH * CUBE_WIDTH)
#define CUBE_VOLUME (CUBE_WIDTH * CUBE_AREA)

#endif //ndef __CUBEHEAD_H
