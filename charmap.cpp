#include "charmap.h"
#include <stdio.h>
#include <string.h>
#include "charmaps/chm_upper.h"
#include "charmaps/chm_lower.h"
#include "charmaps/chm_digit.h"
#include "charmaps/chm_punct.h"
#include "charmaps/chm_paren.h"
#include "charmaps/chm_shape.h"
#include "charmaps/chm_misc.h"

#if defined(ARDUINO) && defined(USE_PROGMEM)
	#include <avr/pgmspace.h>
#endif

#ifdef CHARMAP_COMPRESS
	//#pragma message "using compressed charmaps"
#endif

#ifdef INVALID_SPACE
	#define INVALID_CHAR _c20
#else
	#define INVALID_CHAR NULL
#endif

namespace ledcube {

namespace charmap {

//ascii 32 - 126
static const unsigned char* const ascii_map[] PROGMEM_ENABLED =
{
	_c20, _c21, _c22, _c23, _c24, _c25, _c26, _c27, _c28, _c29, _c2a, _c2b, _c2c, _c2d, _c2e, _c2f,
	_c30, _c31, _c32, _c33, _c34, _c35, _c36, _c37, _c38, _c39, _c3a, _c3b, _c3c, _c3d, _c3e, _c3f,
	_c40, _c41, _c42, _c43, _c44, _c45, _c46, _c47, _c48, _c49, _c4a, _c4b, _c4c, _c4d, _c4e, _c4f,
	_c50, _c51, _c52, _c53, _c54, _c55, _c56, _c57, _c58, _c59, _c5a, _c5b, _c5c, _c5d, _c5e, _c5f,
	_c60, _c61, _c62, _c63, _c64, _c65, _c66, _c67, _c68, _c69, _c6a, _c6b, _c6c, _c6d, _c6e, _c6f,
	_c70, _c71, _c72, _c73, _c74, _c75, _c76, _c77, _c78, _c79, _c7a, _c7b, _c7c, _c7d, _c7e, INVALID_CHAR,
};

static const unsigned char *chmap_getch(char c)
{
	if(c < 0x20 || c > 0x7e)
		return INVALID_CHAR;

#ifdef USE_PROGMEM
	return (unsigned char*)pgm_read_ptr(ascii_map + c - 32);
#else
	return ascii_map[c - 32];
#endif
}

void buildframe(Cubeframe &fr, const unsigned char *ascii, uint16_t delay)
{
#ifdef CHARMAP_COMPRESS
	fr.set(0);

	cubecol n = 0;
	for (uint8_t c = 0; c < CUBELVL_SIZE; c++)
	{
		for (uint8_t x = 0; x < 8; x++)
		{
		#ifdef USE_PROGMEM
			uint8_t a = pgm_read_byte(ascii + c);
		#else
			uint8_t a = ascii[c];
		#endif

			if(a & (1 << (7 - x)))
				fr.set_voxel(1, n % CUBE_WIDTH, n / CUBE_WIDTH, 0);

			n++;
			if(n == CUBE_AREA)
				break;
		}
	}
#else
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		fr.set_level(0, y);
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
		{
		#ifdef USE_PROGMEM
			uint8_t a = pgm_read_byte(ascii + y * CUBE_WIDTH + x);
		#else
			uint8_t a = *(ascii + y * CUBE_WIDTH + x);
		#endif

			if(a == CM_ON)
				fr.set_voxel(1, x, y, 0);
		}
	}
#endif

	fr.delayms = delay;
}

Cubeframe *buildstr(const char *str, size_t *count, uint16_t delay, bool startblank)
{
	*count = 0;

	for (const char *p = str; *p; p++)
	{
		if(chmap_getch(*p))
			(*count)++;
	}

	if(!*count)
		return NULL;

	if(startblank)
		(*count)++;
/*
	struct cubeframe *frames = (struct cubeframe*)malloc(*count * sizeof(struct cubeframe));
	if(!frames)
	{
		*count = -1;
		return NULL;
	}
*/
	Cubeframe *frames = new Cubeframe[*count];
	Cubeframe *curframe = frames;

	if(startblank)
	{
		buildframe(*curframe, chmap_getch(' '), delay);
		curframe++;
	}

	for (const char *p = str; *p; p++)
	{
		const unsigned char *c = chmap_getch(*p);
		if(!c)
			continue;

		buildframe(*curframe, c, delay);
		curframe++;
	}

	return frames;
}

void scrolltext(const Cubeframe *frames, size_t count, uint8_t direction, size_t spacing)
{
	const Cubeframe *fr = frames;
	const Cubeframe *next = frames + 1;
	Cubeframe cur;
	Cubeframe empty;

	cur = *fr;
	empty.set(0);

	cur.draw_frame();

	size_t spoff = CUBE_WIDTH + spacing;
	uint8_t off;

	for (size_t i = 0; i < count; i++, fr++, next++)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			break;
	#endif

		if(i == count - 1)
		{
			next = &empty;
			spoff = CUBE_WIDTH;
		}

		for (size_t s = 0; s < spoff; s++)
		{
			off = s - spacing;

			if(direction == DIR_UP || direction == DIR_DOWN)
			{
				for (uint8_t x = 0; x < CUBE_WIDTH; x++)
				{
					if(direction == DIR_UP)
					{
						for (uint8_t y = 1; y < CUBE_WIDTH; y++)
							cur.set_voxel(cur.get_voxel(x, y, 0), x, y - 1, 0);

						if(s < spacing)
						{
							cur.set_voxel(0, x, CUBE_WIDTH - 1, 0);
						}else
						{
							cur.set_voxel(next->get_voxel(x, off, 0), x, CUBE_WIDTH - 1, 0);
						}
					}else
					{
						for (uint8_t y = CUBE_WIDTH - 2; ; y--)
						{
							cur.set_voxel(cur.get_voxel(x, y, 0), x, y + 1, 0);
							if(!y)
								break;
						}

						if(s < spacing)
						{
							cur.set_voxel(0, x, 0, 0);
						}else
						{
							cur.set_voxel(next->get_voxel(x, CUBE_WIDTH - off - 1, 0), x, 0, 0);
						}
					}
				}
			}else
			{
				for (uint8_t y = 0; y < CUBE_WIDTH; y++)
				{
					if(direction == DIR_RIGHT)
					{
						for (uint8_t x = CUBE_WIDTH - 2; ; x--)
						{
							cur.set_voxel(cur.get_voxel(x, y, 0), x + 1, y, 0);
							if(!x)
								break;
						}

						if(s < spacing)
						{
							cur.set_voxel(0, 0, y, 0);
						}else
						{
							cur.set_voxel(next->get_voxel(CUBE_WIDTH - off - 1, y, 0), 0, y, 0);
						}
					}else
					{
						for (uint8_t x = 1; x < CUBE_WIDTH; x++)
							cur.set_voxel(cur.get_voxel(x, y, 0), x - 1, y, 0);

						if(s < spacing)
						{
							cur.set_voxel(0, CUBE_WIDTH - 1, y, 0);
						}else
						{
							cur.set_voxel(next->get_voxel(off, y, 0), CUBE_WIDTH - 1, y, 0);
						}
					}
				}
			}

			cur.draw_frame();
		}
	}
}

} //namespace charmap

} //namespace ledcube
