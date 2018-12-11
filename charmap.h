#ifndef __CHARMAP_H
#define __CHARMAP_H

#ifdef TEST_NOTEENSY
	#include <malloc.h>
#endif

#include <stdint.h>
#include "cubemap.h"

#define CHMAP_WIDTH 5

#ifndef CHMAP_WIDTH
	#define CHMAP_WIDTH 0
#endif

namespace ledcube
{

#if CHMAP_WIDTH == CUBE_WIDTH
namespace charmap
{
	void buildframe(Cubeframe &fr, const char *ascii, uint16_t delay);
	Cubeframe *buildstr(const char *str, size_t *count, uint16_t delay);
	void scrolltext(const struct cubeframe *frames, size_t count, uint8_t direction, size_t spacing);
}
#endif

}
#endif //ndef __CHARMAP_H
