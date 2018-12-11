#include "charmap.h"

#if CHMAP_WIDTH == CUBE_WIDTH

#include <stdio.h>
#include <string.h>
#include "chm_upper.h"
#include "chm_lower.h"
#include "chm_digit.h"
#include "chm_punct.h"
#include "chm_paren.h"
#include "chm_shape.h"
#include "chm_misc.h"

#ifdef INVALID_SPACE
	#define INVALID_CHAR _c20
#else
	#define INVALID_CHAR NULL
#endif

//32 - 126
const char* const ascii_map[] = {
	_c20, _c21, _c22, _c23, _c24, _c25, _c26, _c27, _c28, _c29, _c2a, _c2b, _c2c, _c2d, _c2e, _c2f,
	_c30, _c31, _c32, _c33, _c34, _c35, _c36, _c37, _c38, _c39, _c3a, _c3b, _c3c, _c3d, _c3e, _c3f,
	_c40, _c41, _c42, _c43, _c44, _c45, _c46, _c47, _c48, _c49, _c4a, _c4b, _c4c, _c4d, _c4e, _c4f,
	_c50, _c51, _c52, _c53, _c54, _c55, _c56, _c57, _c58, _c59, _c5a, _c5b, _c5c, _c5d, _c5e, _c5f,
	_c60, _c61, _c62, _c63, _c64, _c65, _c66, _c67, _c68, _c69, _c6a, _c6b, _c6c, _c6d, _c6e, _c6f,
	_c70, _c71, _c72, _c73, _c74, _c75, _c76, _c77, _c78, _c79, _c7a, _c7b, _c7c, _c7d, _c7e, INVALID_CHAR,
};

const char *chmap_getch(char c)
{
	if(c < 0x20 || c > 0x7e)
		return INVALID_CHAR;
	return ascii_map[c - 32];
}

void chmap_buildframe(struct cubeframe *fr, const char *ascii)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		cm_set_level(fr, 0, y);
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			cm_set_voxel(fr, *(ascii + y * CUBE_WIDTH + x) == CM_ON, x, y, 0);
	}
}

struct cubeframe *chmap_buildstr(const char *str, size_t *count, uint16_t delay)
{
	*count = 0;

	for (const char *p = str; *p; p++)
	{
		if(chmap_getch(*p))
			(*count)++;
	}

	if(!*count)
		return NULL;

	struct cubeframe *frames = (struct cubeframe*)malloc(*count * sizeof(struct cubeframe));
	if(!frames)
	{
		*count = -1;
		return NULL;
	}

	struct cubeframe *curframe = frames;

	for (const char *p = str; *p; p++)
	{
		const char *c = chmap_getch(*p);
		if(!c)
			continue;

		chmap_buildframe(curframe, c);
		curframe->delay = delay;
		curframe++;
	}

	return frames;
}

void chmap_scrolltext(const struct cubeframe *frames, size_t count, uint8_t direction, size_t spacing)
{
	const struct cubeframe *fr = frames;
	const struct cubeframe *next = frames + 1;
	struct cubeframe cur;
	struct cubeframe empty;

	memcpy(&cur, fr, sizeof(struct cubeframe));
	cm_set(&empty, 0);

	cm_draw_frame(&cur);

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
							cm_set_voxel(&cur, cm_get_voxel(&cur, x, y, 0), x, y - 1, 0);

						if(s < spacing)
						{
							cm_set_voxel(&cur, 0, x, CUBE_WIDTH - 1, 0);
						}else
						{
							cm_set_voxel(&cur, cm_get_voxel(next, x, off, 0), x, CUBE_WIDTH - 1, 0);
						}
					}else
					{
						for (uint8_t y = CUBE_WIDTH - 2; ; y--)
						{
							cm_set_voxel(&cur, cm_get_voxel(&cur, x, y, 0), x, y + 1, 0);
							if(!y)
								break;
						}

						if(s < spacing)
						{
							cm_set_voxel(&cur, 0, x, 0, 0);
						}else
						{
							cm_set_voxel(&cur, cm_get_voxel(next, x, CUBE_WIDTH - off - 1, 0), x, 0, 0);
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
							cm_set_voxel(&cur, cm_get_voxel(&cur, x, y, 0), x + 1, y, 0);
							if(!x)
								break;
						}

						if(s < spacing)
						{
							cm_set_voxel(&cur, 0, 0, y, 0);
						}else
						{
							cm_set_voxel(&cur, cm_get_voxel(next, CUBE_WIDTH - off - 1, y, 0), 0, y, 0);
						}
					}else
					{
						for (uint8_t x = 1; x < CUBE_WIDTH; x++)
							cm_set_voxel(&cur, cm_get_voxel(&cur, x, y, 0), x - 1, y, 0);

						if(s < spacing)
						{
							cm_set_voxel(&cur, 0, CUBE_WIDTH - 1, y, 0);
						}else
						{
							cm_set_voxel(&cur, cm_get_voxel(next, off, y, 0), CUBE_WIDTH - 1, y, 0);
						}
					}
				}
			}

			cm_draw_frame(&cur);
		}
	}
}

#endif //CHMAP_WIDTH == CUBE_WIDTH
