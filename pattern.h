#ifndef __PATTERN_H
#define __PATTERN_H

#include "cubemap.h"
#include <stdlib.h>

namespace ledcube
{
	namespace pattern
	{
		void alternate_full(Cubeframe &fr, uint8_t zero_on);
		void border(Cubeframe &fr, uint8_t led_on, uint8_t width);
		void random(Cubeframe &fr);
		void random_modify(Cubeframe &fr, Cubeframe &ref, size_t count);

		void border_bounce(size_t count, uint16_t delay);
		void border_spin(uint8_t clockwise, cubeperim voxelperlevel, size_t count, uint16_t delay);
		void firework(uint16_t launchdelay, uint16_t explosiondelay);
		void plane_bounce(size_t count, uint16_t delay);
		void rain(size_t count, uint16_t delay);
		void random_set(uint8_t led_on, uint16_t delay);
		void send_voxel(uint8_t axis, size_t count, uint16_t delay, uint16_t leveldelay);
		void stream(uint8_t axdir, size_t count, size_t spacing, uint16_t delay);
	}
}
#endif //ndef __PATTERN_H
