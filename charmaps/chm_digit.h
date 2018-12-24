#ifndef __CHM_DIGIT_H
#define __CHM_DIGIT_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "character maps are not designed for cube width specified"
#endif

namespace ledcube {

namespace charmap {

//0
const unsigned char _c30[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".###."
	"#..##"
	"#.#.#"
	"##..#"
	".###."
, PROTECT({0x74, 0xeb, 0x97, 0x00}) );
//1
const unsigned char _c31[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"..#.."
	"..#.."
	"..#.."
	".###."
, PROTECT({0x61, 0x08, 0x47, 0x00}) );
//2
const unsigned char _c32[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"#..#."
	"..#.."
	".#..."
	"####."
, PROTECT({0x64, 0x88, 0x8f, 0x00}) );
//3
const unsigned char _c33[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"###.."
	"...#."
	".##.."
	"...#."
	"####."
, PROTECT({0xe0, 0x98, 0x2f, 0x00}) );
//4
const unsigned char _c34[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"#..#."
	"#..#."
	"####."
	"...#."
	"...#."
, PROTECT({0x94, 0xbc, 0x21, 0x00}) );
//5
const unsigned char _c35[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"####."
	"#...."
	"###.."
	"...#."
	"###.."
, PROTECT({0xf4, 0x38, 0x2e, 0x00}) );
//6
const unsigned char _c36[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"#...."
	"###.."
	"#..#."
	".##.."
, PROTECT({0x64, 0x39, 0x26, 0x00}) );
//7
const unsigned char _c37[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"####."
	"...#."
	"..#.."
	".#..."
	"#...."
, PROTECT({0xf0, 0x88, 0x88, 0x00}) );
//8
const unsigned char _c38[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"#..#."
	".##.."
	"#..#."
	".##.."
, PROTECT({0x64, 0x99, 0x26, 0x00}) );
//9
const unsigned char _c39[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"#..#."
	".###."
	"...#."
	"...#."
, PROTECT({0x64, 0x9c, 0x21, 0x00}) );

} //namespace ledcube

} //namespace charmap

#endif //ndef __CHM_DIGIT_H
