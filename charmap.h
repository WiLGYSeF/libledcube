#ifndef __CHARMAP_H
#define __CHARMAP_H

#include <stdint.h>
#include <stdlib.h>
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
	Cubeframe *buildstr(const char *str, size_t *count, uint16_t delay, bool startblank);
	void scrolltext(const Cubeframe *frames, size_t count, uint8_t direction, size_t spacing);
}
#endif

}
#endif //ndef __CHARMAP_H
