#include <string.h>
#include "cubemap.h"
#include "pins.h"

#ifdef TEST_NOTEENSY
	#include <stdio.h>
	#include <unistd.h>
#else
	#include <SPI.h>
#endif

const uint8_t pin_ymap[] = {
	_PNA,
	_PNB,
	_PNC,
	_PND,
	_PNE
};

#ifdef CUBE_CURFRAME
	struct cubeframe g_curframe = {0};
#endif
#ifdef PATTERN_KILLFLAG
	volatile int g_patternKillFlag = 0;
#endif

cubecol cm_xz_to_col(uint8_t x, uint8_t z)
{
	return z * CUBE_WIDTH + x;
}

uint16_t cm_col_to_xz(cubecol col)
{
	return ((col % CUBE_WIDTH) << 8) | (col / CUBE_WIDTH);
}

uint8_t cm_get_col(const cubelvl level, cubecol col)
{
	return !!(level[col >> 3] & (1 << (col & 7)));
}

uint8_t cm_get_xz(const cubelvl level, uint8_t x, uint8_t z)
{
	return cm_get_col(level, z * CUBE_WIDTH + x);
}

uint8_t cm_get_voxel(const struct cubeframe *fr, uint8_t x, uint8_t y, uint8_t z)
{
	return cm_get_xz(fr->levels[y], x, z);
}

void cm_set_col(cubelvl level, uint8_t led_on, cubecol col)
{
	if(led_on)
	{
		level[col >> 3] |= (1 << (col & 7));
	}else
	{
		level[col >> 3] &= ~(1 << (col & 7));
	}
}

void cm_set_xz(cubelvl level, uint8_t led_on, uint8_t x, uint8_t z)
{
	cm_set_col(level, led_on, z * CUBE_WIDTH + x);
}

void cm_set_voxel(struct cubeframe *fr, uint8_t led_on, uint8_t x, uint8_t y, uint8_t z)
{
	cm_set_xz(fr->levels[y], led_on, x, z);
}

void cm_set_level(struct cubeframe *fr, uint8_t led_on, uint8_t y)
{
	memset(fr->levels[y], led_on ? 255 : 0, CUBELVL_SIZE);
}

void cm_set(struct cubeframe *fr, uint8_t led_on)
{
	memset(fr->levels, led_on ? 255 : 0, CUBELVL_SIZE * CUBE_WIDTH);
}

//columns and planes:
//perpendicular to n-axis, n is constant

void cm_xrow(struct cubeframe *fr, uint8_t led_on, uint8_t x, uint8_t y)
{
	for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		cm_set_voxel(fr, led_on, x, y, z);
}

void cm_ycol(struct cubeframe *fr, uint8_t led_on, uint8_t x, uint8_t z)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		cm_set_voxel(fr, led_on, x, y, z);
}

void cm_zrow(struct cubeframe *fr, uint8_t led_on, uint8_t y, uint8_t z)
{
	for (uint8_t x = 0; x < CUBE_WIDTH; x++)
		cm_set_voxel(fr, led_on, x, y, z);
}

void cm_get_xplane(const struct cubeframe *fr, cubelvl plane, uint8_t x)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
			cm_set_col(plane, cm_get_voxel(fr, x, y, z), y * CUBE_WIDTH + z);
	}
}

void cm_get_yplane(const struct cubeframe *fr, cubelvl plane, uint8_t y)
{
	memcpy(plane, fr->levels[y], CUBELVL_SIZE);
}

void cm_get_zplane(const struct cubeframe *fr, cubelvl plane, uint8_t z)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			cm_set_col(plane, cm_get_voxel(fr, x, y, z), y * CUBE_WIDTH + x);
	}
}

void cm_set_xplane(struct cubeframe *fr, const cubelvl plane, uint8_t x)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
			cm_set_voxel(fr, cm_get_col(plane, y * CUBE_WIDTH + z), x, y, z);
	}
}

void cm_set_yplane(struct cubeframe *fr, const cubelvl plane, uint8_t y)
{
	memcpy(fr->levels[y], plane, CUBELVL_SIZE);
}

void cm_set_zplane(struct cubeframe *fr, const cubelvl plane, uint8_t z)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			cm_set_voxel(fr, cm_get_col(plane, y * CUBE_WIDTH + x), x, y, z);
	}
}

void cm_xplane(struct cubeframe *fr, uint8_t led_on, uint8_t x)
{
	cubelvl plane;
	memset(plane, led_on ? 255 : 0, CUBELVL_SIZE);
	cm_set_xplane(fr, plane, x);
}

void cm_yplane(struct cubeframe *fr, uint8_t led_on, uint8_t y)
{
	cm_set_level(fr, led_on, y);
}

void cm_zplane(struct cubeframe *fr, uint8_t led_on, uint8_t z)
{
	cubelvl plane;
	memset(plane, led_on ? 255 : 0, CUBELVL_SIZE);
	cm_set_zplane(fr, plane, z);
}

void cm_shift_plane(struct cubeframe *fr, uint8_t axisdir)
{
	cubelvl tmp;

	if(GETAXIS(axisdir) == AXIS_X)
	{
		cubelvl plane;

		if(GETDIR(axisdir) == DIR_BACKWARD)
		{
			cm_get_xplane(fr, tmp, 0);
			for (uint8_t x = 0; x < CUBE_WIDTH - 1; x++)
			{
				cm_get_xplane(fr, plane, x + 1);
				cm_set_xplane(fr, plane, x);
			}
			cm_set_xplane(fr, tmp, CUBE_WIDTH - 1);
		}else
		{
			cm_get_xplane(fr, tmp, CUBE_WIDTH - 1);
			for (uint8_t x = CUBE_WIDTH - 1; x != 0; x--)
			{
				cm_get_xplane(fr, plane, x - 1);
				cm_set_xplane(fr, plane, x);
			}
			cm_set_xplane(fr, tmp, 0);
		}
	}else
	if(GETAXIS(axisdir) == AXIS_Y)
	{
		if(GETDIR(axisdir) == DIR_BACKWARD)
		{
			memcpy(tmp, fr->levels[0], CUBELVL_SIZE);
			memmove(fr->levels[0], fr->levels[1], (CUBE_WIDTH - 1) * CUBELVL_SIZE);
			memcpy(fr->levels[CUBE_WIDTH - 1], tmp, CUBELVL_SIZE);
		}else
		{
			memcpy(tmp, fr->levels[CUBE_WIDTH - 1], CUBELVL_SIZE);
			memmove(fr->levels[1], fr->levels[0], (CUBE_WIDTH - 1) * CUBELVL_SIZE);
			memcpy(fr->levels[0], tmp, CUBELVL_SIZE);
		}
	}else
	if(GETAXIS(axisdir) == AXIS_Z)
	{
		cubelvl plane;

		if(GETDIR(axisdir) == DIR_BACKWARD)
		{
			cm_get_zplane(fr, tmp, 0);
			for (uint8_t z = 0; z < CUBE_WIDTH - 1; z++)
			{
				cm_get_zplane(fr, plane, z + 1);
				cm_set_zplane(fr, plane, z);
			}
			cm_set_zplane(fr, tmp, CUBE_WIDTH - 1);
		}else
		{
			cm_get_zplane(fr, tmp, CUBE_WIDTH - 1);
			for (uint8_t z = CUBE_WIDTH - 1; z != 0; z--)
			{
				cm_get_zplane(fr, plane, z - 1);
				cm_set_zplane(fr, plane, z);
			}
			cm_set_zplane(fr, tmp, 0);
		}
	}
}

void cm_reverse_plane(cubelvl plane, uint8_t dir)
{
	uint8_t half = CUBE_WIDTH / 2 - (CUBE_WIDTH & 1);
	uint8_t v;

	dir &= 3;

	if(dir == DIR_UP || dir == DIR_DOWN)
	{
		for (uint8_t z = 0; z <= half; z++)
		{
			for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			{
				v = cm_get_xz(plane, x, z);
				cm_set_xz(plane, cm_get_xz(plane, x, CUBE_WIDTH - z - 1), x, z);
				cm_set_xz(plane, v, x, CUBE_WIDTH - z - 1);
			}
		}
	}else
	if(dir == DIR_LEFT || dir == DIR_RIGHT)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		{
			for (uint8_t x = 0; x <= half; x++)
			{
				v = cm_get_xz(plane, x, z);
				cm_set_xz(plane, cm_get_xz(plane, CUBE_WIDTH - x - 1, z), x, z);
				cm_set_xz(plane, v, CUBE_WIDTH - x - 1, z);
			}
		}
	}
}

//rotates counterclockwise
void cm_rotate_plane(cubelvl plane, uint8_t times)
{
	cubelvl rotated;
	uint8_t v;

	memset(rotated, 0, sizeof(rotated));

	for (times &= 3; times != 0; times--)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		{
			for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			{
				v = cm_get_xz(plane, x, z);
				cm_set_xz(rotated, v, z, CUBE_WIDTH - x - 1);
			}
		}

		memcpy(plane, rotated, sizeof(cubelvl));
	}
}

#if !defined(TEST_NOTEENSY) && defined(USE_SPI)
void cm_setup_SPI()
{
	SPI.begin();
	SPI.beginTransaction(SPISettings(24000000, LSBFIRST, SPI_MODE0));
}
#endif

void shiftout_level(const cubelvl level)
{
#ifndef TEST_NOTEENSY
	digitalWriteFast(_PLATCH, LOW);

#ifdef USE_SPI
	#error "SPI not yet implemented"
/*
	for (uint8_t b = 0; b < CUBELVL_SIZE; b++)
		SPI.transfer(level[b]);
*/
#else //USE_SPI
	digitalWriteFast(_PCLOCK, LOW);

	digitalWriteFast(_PDATA, 0);
/*
	//for explicit padding

	for (uint8_t b = 8 - (CUBE_AREA % 8); b != 0; b--)
	{
		digitalWriteFast(_PCLOCK, HIGH);
		digitalWriteFast(_PCLOCK, LOW);
	}

	for (uint8_t i = 0; i < (CUBE_AREA & 7); i++)
	{
		digitalWriteFast(_PDATA, !!(level[0] & (1 << i)));
		digitalWriteFast(_PCLOCK, HIGH);
		digitalWriteFast(_PCLOCK, LOW);
	}

	for (uint8_t b = 1; b < CUBELVL_SIZE; b++)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			digitalWriteFast(_PDATA, !!(level[b] & (1 << i)));
			digitalWriteFast(_PCLOCK, HIGH);
			digitalWriteFast(_PCLOCK, LOW);
		}
	}
*/

	for (uint16_t i = 0; i < CUBE_AREA; i++)
	{
		digitalWriteFast(_PDATA, !!(level[i >> 3] & (1 << (i & 7))));
		digitalWriteFast(_PCLOCK, HIGH);
		digitalWriteFast(_PCLOCK, LOW);
	}

#endif //USE_SPI

	digitalWriteFast(_PLATCH, HIGH);
#endif //ndef TEST_NOTEENSY
}

void cm_draw_level(const struct cubeframe *fr, uint8_t y)
{
#ifndef TEST_NOTEENSY
	for (uint8_t i = 0; i < CUBE_WIDTH; i++)
		digitalWrite(pin_ymap[i], LOW);

	shiftout_level(fr->levels[y]);

	digitalWrite(pin_ymap[y], HIGH);
#endif
}

void cm_draw_frame(const struct cubeframe *fr)
{
#ifdef TEST_NOTEENSY
	cm_print_frame(fr);
	usleep(fr->delay * 1000);
#else
	uint16_t loops = fr->delay / CUBE_WIDTH / LEVEL_DELAY;
	if(!loops)
		loops = 1;

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		digitalWrite(pin_ymap[y], LOW);

	for (; loops; loops--)
	{
		for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		{
			digitalWrite(pin_ymap[y ? y - 1 : CUBE_WIDTH - 1], LOW);
			shiftout_level(fr->levels[y]);
			digitalWrite(pin_ymap[y], HIGH);
			delay(LEVEL_DELAY);
		}
	}
#endif

#ifdef CUBE_CURFRAME
	memcpy(&g_curframe, fr, sizeof(struct cubeframe));
#endif
}

void cm_delay_frame(uint16_t delayms)
{
#ifdef TEST_NOTEENSY
	usleep(delayms * 1000);
#else
	uint16_t loops = delayms / CUBE_WIDTH / LEVEL_DELAY;
	if(!loops)
		loops = 1;

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		digitalWrite(pin_ymap[y], LOW);

	for (; loops; loops--)
	{
		for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		{
			digitalWrite(pin_ymap[y ? y - 1 : CUBE_WIDTH - 1], LOW);
			digitalWrite(pin_ymap[y], HIGH);

		#ifndef TEST_NOTEENSY
			delay(LEVEL_DELAY);
		#endif
		}
	}
#endif
}

#ifdef TEST_NOTEENSY
void cm_print_plane(const cubelvl plane, uint8_t multilevel)
{
	for (uint8_t z = 0; z < CUBE_WIDTH; z++)
	{
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			putchar(cm_get_xz(plane, x, z) ? CM_ON : CM_OFF);
		putchar(multilevel ? ' ' : '\n');
	}

	putchar('\n');
}

void cm_print_frame(const struct cubeframe *fr)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		cm_print_plane(fr->levels[y], 1);
	putchar('\n');
}
#endif
