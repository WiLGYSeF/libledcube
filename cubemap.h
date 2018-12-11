#ifndef __CUBEMAP_H
#define __CUBEMAP_H

#include <stdint.h>
#include "cubehead.h"

//#define CUBE_CURFRAME
//#define TEST_NOTEENSY
//#define USE_SPI

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
	#define LEVEL_DELAY 2 //maximum is 3
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

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t cubelvl[CUBELVL_SIZE];
#if CUBE_WIDTH < 16
	typedef uint8_t cubecol;
#else
	typedef uint16_t cubecol;
#endif
#if CUBE_WIDTH <= 64
	typedef uint8_t cubeperim;
#else
	typedef uint16_t cubeperim;
#endif
#if CUBE_WIDTH <= 6
	typedef uint8_t cubevol;
#elif CUBE_WIDTH <= 40
	typedef uint16_t cubevol;
#else
	typedef size_t cubevol;
#endif

struct cubeframe {
	uint16_t delay;
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

	 0  1  2  3  4: 5  6  7
	 8  9:10 11 12 13 14:15
	16 17 18 19:20 21 22 23
	24
*/
	cubelvl levels[CUBE_WIDTH];
};

cubecol cm_xz_to_col(uint8_t x, uint8_t z);
uint16_t cm_col_to_xz(cubecol col);

uint8_t cm_get_col(const cubelvl level, cubecol col);
uint8_t cm_get_xz(const cubelvl level, uint8_t x, uint8_t z);
uint8_t cm_get_voxel(const struct cubeframe *fr, uint8_t x, uint8_t y, uint8_t z);
void cm_set_col(cubelvl level, uint8_t led_on, cubecol col);
void cm_set_xz(cubelvl level, uint8_t led_on, uint8_t x, uint8_t z);
void cm_set_voxel(struct cubeframe *fr, uint8_t led_on, uint8_t x, uint8_t y, uint8_t z);
void cm_set_level(struct cubeframe *fr, uint8_t led_on, uint8_t y);
void cm_set(struct cubeframe *fr, uint8_t led_on);

void cm_xrow(struct cubeframe *fr, uint8_t led_on, uint8_t x, uint8_t y);
void cm_ycol(struct cubeframe *fr, uint8_t led_on, uint8_t x, uint8_t z);
void cm_zrow(struct cubeframe *fr, uint8_t led_on, uint8_t y, uint8_t z);
void cm_get_xplane(const struct cubeframe *fr, cubelvl plane, uint8_t x);
void cm_get_yplane(const struct cubeframe *fr, cubelvl plane, uint8_t y);
void cm_get_zplane(const struct cubeframe *fr, cubelvl plane, uint8_t z);
void cm_set_xplane(struct cubeframe *fr, const cubelvl plane, uint8_t x);
void cm_set_yplane(struct cubeframe *fr, const cubelvl plane, uint8_t y);
void cm_set_zplane(struct cubeframe *fr, const cubelvl plane, uint8_t z);
void cm_xplane(struct cubeframe *fr, uint8_t led_on, uint8_t x);
void cm_yplane(struct cubeframe *fr, uint8_t led_on, uint8_t y);
void cm_zplane(struct cubeframe *fr, uint8_t led_on, uint8_t z);

void cm_shift_plane(struct cubeframe *fr, uint8_t axisdir);
void cm_reverse_plane(cubelvl plane, uint8_t dir);
void cm_rotate_plane(cubelvl plane, uint8_t times);

#if !defined(TEST_NOTEENSY) && defined(USE_SPI)
	void cm_setup_SPI();
#endif
void cm_draw_frame(const struct cubeframe *fr);
void cm_delay_frame(uint16_t delayms);
#ifdef TEST_NOTEENSY
	void cm_print_plane(const cubelvl plane, uint8_t multilevel);
	void cm_print_frame(const struct cubeframe *fr);
#endif

#ifdef CUBE_CURFRAME
	extern struct cubeframe g_curframe;
#endif
#ifdef PATTERN_KILLFLAG
	extern volatile int g_patternKillFlag;
#endif

#ifdef __cplusplus
}
#endif

#endif //ndef __CUBEMAP_H
