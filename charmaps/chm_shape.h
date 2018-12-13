#ifndef __CHM_SHAPE_H
#define __CHM_SHAPE_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

const unsigned char _chm_heart[] =
CHARMAP_DATA(
	".#.#."
	"#####"
	"#####"
	".###."
	"..#.."
, PROTECT({0x57, 0xfe, 0xe2, 0x00}) );

const unsigned char _chm_smileyface[] =
CHARMAP_DATA(
	"##.##"
	"##.##"
	"....."
	"#...#"
	".###."
, PROTECT({0xde, 0xc1, 0x17, 0x00}) );

const unsigned char _chm_star[] =
CHARMAP_DATA(
	"....."
	"..#.."
	"#####"
	".###."
	"#...#"
, PROTECT({0x01, 0x3e, 0xe8, 0x80}) );

#endif //ndef __CHM_SHAPE_H
