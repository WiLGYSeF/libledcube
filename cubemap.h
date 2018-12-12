#ifndef __CUBEMAP_H
#define __CUBEMAP_H

#include "cubehead.h"
#include <stdint.h>

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

#define DIR_FORWARD 0
#define DIR_BACKWARD 1

#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

#define GETAXIS(AD) ((AD) >> 1)
#define GETDIR(AD) ((AD) & 1)
#define AXISDIR(A,D) ((((A) % 3) << 1) | ((D) & 1))

#ifndef LEVEL_DELAY
	#define LEVEL_DELAY 2 //maximum is 3 for POV for 5x5x5 cube
#endif

#ifndef CM_ON
	#define CM_ON '#'
#endif
#ifndef CM_OFF
	#define CM_OFF '.'
#endif

//check if power of 2
#if CUBE_WIDTH && (!(CUBE_WIDTH & (CUBE_WIDTH - 1)))
	#define CUBELVL_SIZE (CUBE_AREA >> 3)
#else
	#define CUBELVL_SIZE ((CUBE_AREA >> 3) + 1)
#endif
namespace ledcube
{
	//variable type for storing a cube plane
	typedef uint8_t cubelvl[CUBELVL_SIZE];

	//variable type for storing a cube column number, or the cube column x-z coordinates
	#if CUBE_WIDTH < 16
		typedef uint8_t cubecol;
	#else
		typedef uint16_t cubecol;
	#endif

	//variable type for storing a cube perimeter column number
	#if CUBE_WIDTH <= 64
		typedef uint8_t cubeperim;
	#else
		typedef uint16_t cubeperim;
	#endif

	//variable type for storing a cube volume size
	#if CUBE_WIDTH <= 6
		typedef uint8_t cubevol;
	#elif CUBE_WIDTH <= 40
		typedef uint16_t cubevol;
	#else
		typedef uint32_t cubevol;
	#endif

	class Cubeframe
	{
	public:
		uint16_t delayms;
	/*
		level bits
		 20 21 22 23 24
		 15 16 17 18 19
		 10 11 12 13 14
		  5  6  7  8  9
		  0  1  2  3  4
		  ^
		  |
		front left

		x -->

		y .

		  ^
		z |

		 0  1  2  3  4: 5  6  7
		 8  9:10 11 12 13 14:15
		16 17 18 19:20 21 22 23
		24
	*/
		cubelvl levels[CUBE_WIDTH];

		Cubeframe();
		Cubeframe(uint16_t delay);

		static cubecol xz_to_col(uint8_t x, uint8_t z);
		static uint16_t col_to_xz(cubecol col);

		static cubevol xyz_to_vox(uint8_t x, uint8_t y, uint8_t z);
		static uint32_t vox_to_xyz(cubevol v);

		static uint8_t get_col(const cubelvl level, cubecol col);
		static uint8_t get_xz(const cubelvl level, uint8_t x, uint8_t z);
		uint8_t get_voxel(uint8_t x, uint8_t y, uint8_t z) const;

		static void set_col(cubelvl level, uint8_t led_on, cubecol col);
		static void set_xz(cubelvl level, uint8_t led_on, uint8_t x, uint8_t z);

		void set_voxel(uint8_t led_on, uint8_t x, uint8_t y, uint8_t z);
		void set_level(uint8_t led_on, uint8_t y);
		void set(uint8_t led_on);

		void xrow(uint8_t led_on, uint8_t x, uint8_t y);
		void ycol(uint8_t led_on, uint8_t x, uint8_t z);
		void zrow(uint8_t led_on, uint8_t y, uint8_t z);
		void get_xplane(cubelvl plane, uint8_t x) const;
		void get_yplane(cubelvl plane, uint8_t y) const;
		void get_zplane(cubelvl plane, uint8_t z) const;
		void set_xplane(const cubelvl plane, uint8_t x);
		void set_yplane(const cubelvl plane, uint8_t y);
		void set_zplane(const cubelvl plane, uint8_t z);
		void xplane(uint8_t led_on, uint8_t x);
		void yplane(uint8_t led_on, uint8_t y);
		void zplane(uint8_t led_on, uint8_t z);

		void shift_plane(uint8_t axisdir);

		static void reverse_plane(cubelvl plane, uint8_t dir);
		static void rotate_plane(cubelvl plane, uint8_t times);

		void draw_level(uint8_t y) const;
		void draw_frame() const;
		static void delay_frame(uint16_t delayms);
	#ifndef ARDUINO
		static void print_plane(const cubelvl plane, uint8_t multilevel);
		void print_frame() const;
	#endif
	};

	void setup_SPI();

#ifdef CUBE_CURFRAME
	extern Cubeframe g_curframe;
#endif
#ifdef PATTERN_KILLFLAG
	extern volatile int g_patternKillFlag;
#endif
#ifndef ARDUINO
	extern int g_verboseprint;
#endif
}

#endif //ndef __CUBEMAP_H
