#ifndef __CHARMAP_H
#define __CHARMAP_H

#include <stdint.h>
#include <stdlib.h>
#include "cubemap.h"

namespace ledcube
{
	namespace charmap
	{
		void buildframe(Cubeframe &fr, const unsigned char *ascii, uint16_t delay);
		Cubeframe *buildstr(const char *str, size_t *count, uint16_t delay, bool startblank);
		void scrolltext(const Cubeframe *frames, size_t count, uint8_t direction, size_t spacing);
	}
}

#endif //ndef __CHARMAP_H
