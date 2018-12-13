#include "cubemap.h"
#include <string.h>
#include "pins.h"

#ifdef ARDUINO
	#include <SPI.h>

	#ifdef DIGITALWRITE_SLOW
		#define digitalWriteFast(P, V) digitalWrite((P), (V))
	#endif
#else
	#include <stdio.h>
	#include <unistd.h>

	static const char *hex = "0123456789abcdef";
	static const char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#endif

namespace ledcube {

#ifdef CUBE_CURFRAME
	Cubeframe g_curframe;
#endif
#ifdef PATTERN_KILLFLAG
	volatile int g_patternKillFlag = 0;
#endif
#ifndef ARDUINO
	int g_verboseprint = 0;
#endif

Cubeframe::Cubeframe()
{
	this->delayms = 0;
}

Cubeframe::Cubeframe(uint16_t delay)
{
	this->delayms = delay;
}

cubecol Cubeframe::xz_to_col(uint8_t x, uint8_t z)
{
	return z * CUBE_WIDTH + x;
}

uint16_t Cubeframe::col_to_xz(cubecol col)
{
	//arduino complains about type width
	return (( ((uint16_t)col) % CUBE_WIDTH) << 8) | (col / CUBE_WIDTH);
}

cubevol Cubeframe::xyz_to_vox(uint8_t x, uint8_t y, uint8_t z)
{
	return y * CUBE_AREA + Cubeframe::xz_to_col(x, z);
}

uint32_t Cubeframe::vox_to_xyz(cubevol v)
{
	uint8_t x = v % CUBE_WIDTH;
	uint8_t y = v / CUBE_AREA;
	uint8_t z = (v % CUBE_AREA) / CUBE_WIDTH;

	//arduino complains about type width
	return ( ((uint32_t)x) << 16) | ( ((uint16_t)y) << 8) | z;
}

uint8_t Cubeframe::get_col(const cubelvl level, cubecol col)
{
	return !!(level[col >> 3] & (1 << (col & 7)));
}

uint8_t Cubeframe::get_xz(const cubelvl level, uint8_t x, uint8_t z)
{
	return Cubeframe::get_col(level, z * CUBE_WIDTH + x);
}

uint8_t Cubeframe::get_voxel(uint8_t x, uint8_t y, uint8_t z) const
{
	return this->get_xz(this->levels[y], x, z);
}

void Cubeframe::set_col(cubelvl level, uint8_t led_on, cubecol col)
{
	if(led_on)
	{
		level[col >> 3] |= (1 << (col & 7));
	}else
	{
		level[col >> 3] &= ~(1 << (col & 7));
	}
}

void Cubeframe::set_xz(cubelvl level, uint8_t led_on, uint8_t x, uint8_t z)
{
	Cubeframe::set_col(level, led_on, z * CUBE_WIDTH + x);
}

void Cubeframe::set_voxel(uint8_t led_on, uint8_t x, uint8_t y, uint8_t z)
{
	this->set_xz(this->levels[y], led_on, x, z);
}

void Cubeframe::set_level(uint8_t led_on, uint8_t y)
{
	memset(this->levels[y], led_on ? 255 : 0, CUBELVL_SIZE);
}

void Cubeframe::set(uint8_t led_on)
{
	memset(this->levels, led_on ? 255 : 0, CUBELVL_SIZE * CUBE_WIDTH);
}

//columns and planes:
//perpendicular to n-axis, n is constant

void Cubeframe::xrow(uint8_t led_on, uint8_t x, uint8_t y)
{
	for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		this->set_voxel(led_on, x, y, z);
}

void Cubeframe::ycol(uint8_t led_on, uint8_t x, uint8_t z)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		this->set_voxel(led_on, x, y, z);
}

void Cubeframe::zrow(uint8_t led_on, uint8_t y, uint8_t z)
{
	for (uint8_t x = 0; x < CUBE_WIDTH; x++)
		this->set_voxel(led_on, x, y, z);
}

void Cubeframe::get_xplane(cubelvl plane, uint8_t x) const
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
			Cubeframe::set_col(plane, this->get_voxel(x, y, z), y * CUBE_WIDTH + z);
	}
}

void Cubeframe::get_yplane(cubelvl plane, uint8_t y) const
{
	memcpy(plane, this->levels[y], CUBELVL_SIZE);
}

void Cubeframe::get_zplane(cubelvl plane, uint8_t z) const
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			Cubeframe::set_col(plane, this->get_voxel(x, y, z), y * CUBE_WIDTH + x);
	}
}

void Cubeframe::set_xplane(const cubelvl plane, uint8_t x)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
			this->set_voxel(Cubeframe::get_col(plane, y * CUBE_WIDTH + z), x, y, z);
	}
}

void Cubeframe::set_yplane(const cubelvl plane, uint8_t y)
{
	memcpy(this->levels[y], plane, CUBELVL_SIZE);
}

void Cubeframe::set_zplane(const cubelvl plane, uint8_t z)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			this->set_voxel(Cubeframe::get_col(plane, y * CUBE_WIDTH + x), x, y, z);
	}
}

void Cubeframe::xplane(uint8_t led_on, uint8_t x)
{
	cubelvl plane;
	memset(plane, led_on ? 255 : 0, CUBELVL_SIZE);
	this->set_xplane(plane, x);
}

void Cubeframe::yplane(uint8_t led_on, uint8_t y)
{
	this->set_level(led_on, y);
}

void Cubeframe::zplane(uint8_t led_on, uint8_t z)
{
	cubelvl plane;
	memset(plane, led_on ? 255 : 0, CUBELVL_SIZE);
	this->set_zplane(plane, z);
}

void Cubeframe::shift_plane(uint8_t axisdir)
{
	cubelvl tmp;

	if(GETAXIS(axisdir) == AXIS_X)
	{
		cubelvl plane;

		if(GETDIR(axisdir) == DIR_BACKWARD)
		{
			this->get_xplane(tmp, 0);
			for (uint8_t x = 0; x < CUBE_WIDTH - 1; x++)
			{
				this->get_xplane(plane, x + 1);
				this->set_xplane(plane, x);
			}
			this->set_xplane(tmp, CUBE_WIDTH - 1);
		}else
		{
			this->get_xplane(tmp, CUBE_WIDTH - 1);
			for (uint8_t x = CUBE_WIDTH - 1; x != 0; x--)
			{
				this->get_xplane(plane, x - 1);
				this->set_xplane(plane, x);
			}
			this->set_xplane(tmp, 0);
		}
	}else
	if(GETAXIS(axisdir) == AXIS_Y)
	{
		if(GETDIR(axisdir) == DIR_BACKWARD)
		{
			memcpy(tmp, this->levels[0], CUBELVL_SIZE);
			memmove(this->levels[0], this->levels[1], (CUBE_WIDTH - 1) * CUBELVL_SIZE);
			memcpy(this->levels[CUBE_WIDTH - 1], tmp, CUBELVL_SIZE);
		}else
		{
			memcpy(tmp, this->levels[CUBE_WIDTH - 1], CUBELVL_SIZE);
			memmove(this->levels[1], this->levels[0], (CUBE_WIDTH - 1) * CUBELVL_SIZE);
			memcpy(this->levels[0], tmp, CUBELVL_SIZE);
		}
	}else
	if(GETAXIS(axisdir) == AXIS_Z)
	{
		cubelvl plane;

		if(GETDIR(axisdir) == DIR_BACKWARD)
		{
			this->get_zplane(tmp, 0);
			for (uint8_t z = 0; z < CUBE_WIDTH - 1; z++)
			{
				this->get_zplane(plane, z + 1);
				this->set_zplane(plane, z);
			}
			this->set_zplane(tmp, CUBE_WIDTH - 1);
		}else
		{
			this->get_zplane(tmp, CUBE_WIDTH - 1);
			for (uint8_t z = CUBE_WIDTH - 1; z != 0; z--)
			{
				this->get_zplane(plane, z - 1);
				this->set_zplane(plane, z);
			}
			this->set_zplane(tmp, 0);
		}
	}
}

void Cubeframe::reverse_plane(cubelvl plane, uint8_t dir)
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
				v = Cubeframe::get_xz(plane, x, z);
				Cubeframe::set_xz(plane, Cubeframe::get_xz(plane, x, CUBE_WIDTH - z - 1), x, z);
				Cubeframe::set_xz(plane, v, x, CUBE_WIDTH - z - 1);
			}
		}
	}else
	if(dir == DIR_LEFT || dir == DIR_RIGHT)
	{
		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		{
			for (uint8_t x = 0; x <= half; x++)
			{
				v = Cubeframe::get_xz(plane, x, z);
				Cubeframe::set_xz(plane, Cubeframe::get_xz(plane, CUBE_WIDTH - x - 1, z), x, z);
				Cubeframe::set_xz(plane, v, CUBE_WIDTH - x - 1, z);
			}
		}
	}
}

//rotates counterclockwise
void Cubeframe::rotate_plane(cubelvl plane, uint8_t times)
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
				v = Cubeframe::get_xz(plane, x, z);
				Cubeframe::set_xz(rotated, v, z, CUBE_WIDTH - x - 1);
			}
		}

		memcpy(plane, rotated, sizeof(cubelvl));
	}
}

static void shiftout_level(const cubelvl level)
{
#ifdef ARDUINO
	digitalWriteFast(_PLATCH, LOW);

#ifdef USE_SPI
	for (uint8_t b = 0; b < CUBELVL_SIZE; b++)
		SPI.transfer(level[b]);
#else //USE_SPI
	digitalWriteFast(_PCLOCK, LOW);

/*
	//for explicit padding
	digitalWriteFast(_PDATA, 0);

	for (uint8_t b = 8 - (CUBE_AREA & 7); b != 0; b--)
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
#endif //else USE_SPI

	digitalWriteFast(_PLATCH, HIGH);
#endif //def ARDUINO
}

void Cubeframe::draw_level(uint8_t y) const
{
#ifdef ARDUINO
	for (uint8_t i = 0; i < CUBE_WIDTH; i++)
		digitalWrite(PIN_YARR[i], LOW);

	shiftout_level(this->levels[y]);

	digitalWrite(PIN_YARR[y], HIGH);
#endif
}

void Cubeframe::draw_frame() const
{
#ifdef ARDUINO
	uint16_t loops = this->delayms / CUBE_WIDTH / LEVEL_DELAY;
	if(!loops)
		loops = 1;

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		digitalWrite(PIN_YARR[y], LOW);

	for (; loops; loops--)
	{
		for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		{
			digitalWrite(PIN_YARR[y ? y - 1 : CUBE_WIDTH - 1], LOW);
			shiftout_level(this->levels[y]);
			digitalWrite(PIN_YARR[y], HIGH);
			delay(LEVEL_DELAY);
		}
	}
#else
	this->print_frame();
	usleep(this->delayms * 1000);
#endif

#ifdef CUBE_CURFRAME
	//copy the last frame drawn
	g_curframe = this;
#endif
}

void Cubeframe::delay_frame(uint16_t delayms)
{
#ifdef ARDUINO
	uint16_t loops = delayms / CUBE_WIDTH / LEVEL_DELAY;
	if(!loops)
		loops = 1;

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		digitalWrite(PIN_YARR[y], LOW);

	for (; loops; loops--)
	{
		for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		{
			digitalWrite(PIN_YARR[y ? y - 1 : CUBE_WIDTH - 1], LOW);
			digitalWrite(PIN_YARR[y], HIGH);
			delay(LEVEL_DELAY);
		}
	}
#else
	usleep(delayms * 1000);
#endif
}

#ifndef ARDUINO
void Cubeframe::print_plane(const cubelvl plane, uint8_t multilevel)
{
	for (uint8_t z = 0; z < CUBE_WIDTH; z++)
	{
		for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			putchar(Cubeframe::get_xz(plane, x, z) ? CM_ON : CM_OFF);
		putchar(multilevel ? ' ' : '\n');
	}

	putchar('\n');
}

void Cubeframe::print_frame() const
{
	if(g_verboseprint && CUBE_WIDTH <= 64)
	{
		putchar(' ');
		putchar(' ');

		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		{
			if(CUBE_WIDTH <= 16)
			{
				putchar(hex[z]);
			}else
			if(CUBE_WIDTH <= 64)
			{
				putchar(base64[z]);
			}

			for (uint8_t w = 0; w < CUBE_WIDTH; w++)
				putchar(' ');
		}

		putchar('z');
		putchar('\n');

		putchar('y');
		putchar('\n');
	}

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		if(g_verboseprint)
		{
			if(CUBE_WIDTH <= 16)
			{
				putchar(hex[y]);
			}else
			if(CUBE_WIDTH <= 64)
			{
				putchar(base64[y]);
			}else
			{
				putchar(' ');
			}

			putchar(' ');
		}

		Cubeframe::print_plane(this->levels[y], 1);
	}
	putchar('\n');

	if(g_verboseprint && CUBE_WIDTH <= 64)
	{
		putchar(' ');
		putchar(' ');

		for (uint8_t z = 0; z < CUBE_WIDTH; z++)
		{
			for (uint8_t x = 0; x < CUBE_WIDTH; x++)
			{
				if(CUBE_WIDTH <= 16)
				{
					putchar(hex[x]);
				}else
				if(CUBE_WIDTH <= 64)
				{
					putchar(base64[x]);
				}else
				{
					putchar(' ');
				}
			}

			putchar(' ');
		}

		putchar('x');
		putchar('\n');
		putchar('\n');
	}
}

void setup_SPI()
{
#if defined(ARDUINO) && defined(USE_SPI)
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0));
#endif
}

#endif //else ndef ARDUINO

} //namespace ledcube
