#ifndef __CHM_PUNCT_H
#define __CHM_PUNCT_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//
const unsigned char _c20[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"....."
	"....."
	"....."
	"....."
	"....."
, PROTECT({0x00, 0x00, 0x00, 0x00}) );
//!
const unsigned char _c21[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..#.."
	"..#.."
	"..#.."
	"....."
	"..#.."
, PROTECT({0x21, 0x08, 0x02, 0x00}) );
//"
const unsigned char _c22[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..##."
	"..##."
	"....."
	"....."
	"....."
, PROTECT({0x31, 0x80, 0x00, 0x00}) );
//'
const unsigned char _c27[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..#.."
	"..#.."
	"....."
	"....."
	"....."
, PROTECT({0x21, 0x00, 0x00, 0x00}) );
//,
const unsigned char _c2c[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"....."
	"....."
	"..##."
	"...#."
	"..#.."
, PROTECT({0x00, 0x0c, 0x22, 0x00}) );
//.
const unsigned char _c2e[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"....."
	"....."
	"....."
	"..##."
	"..##."
, PROTECT({0x00, 0x00, 0x63, 0x00}) );
//:
const unsigned char _c3a[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..#.."
	"..#.."
	"....."
	"..#.."
	"..#.."
, PROTECT({0x21, 0x00, 0x42, 0x00}) );
//;
const unsigned char _c3b[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..#.."
	"..#.."
	"....."
	"...#."
	"..#.."
, PROTECT({0x21, 0x00, 0x22, 0x00}) );
//?
const unsigned char _c3f[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"#..#."
	"...#."
	"..#.."
	"..#.."
, PROTECT({0x64, 0x84, 0x42, 0x00}) );

#endif //ndef __CHM_PUNCT_H
