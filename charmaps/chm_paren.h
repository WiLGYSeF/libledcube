#ifndef __CHM_PAREN_H
#define __CHM_PAREN_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//(
const unsigned char _c28[] =
CHARMAP_DATA(
	"..##."
	".#..."
	".#..."
	".#..."
	"..##."
, PROTECT({0x32, 0x10, 0x83, 0x00}) );
//)
const unsigned char _c29[] =
CHARMAP_DATA(
	".##.."
	"...#."
	"...#."
	"...#."
	".##.."
, PROTECT({0x60, 0x84, 0x26, 0x00}) );
//[
const unsigned char _c5b[] =
CHARMAP_DATA(
	"###.."
	"#...."
	"#...."
	"#...."
	"###.."
, PROTECT({0xe4, 0x21, 0x0e, 0x00}) );
//]
const unsigned char _c5d[] =
CHARMAP_DATA(
	"..###"
	"....#"
	"....#"
	"....#"
	"..###"
, PROTECT({0x38, 0x42, 0x13, 0x80}) );
//{
const unsigned char _c7b[] =
CHARMAP_DATA(
	"..##."
	".#..."
	"##..."
	".#..."
	"..##."
, PROTECT({0x32, 0x30, 0x83, 0x00}) );
//}
const unsigned char _c7d[] =
CHARMAP_DATA(
	".##.."
	"...#."
	"...##"
	"...#."
	".##.."
, PROTECT({0x60, 0x86, 0x26, 0x00}) );

#endif //ndef __CHM_PAREN_H
