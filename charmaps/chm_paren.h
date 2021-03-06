#ifndef __CHM_PAREN_H
#define __CHM_PAREN_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "character maps are not designed for cube width specified"
#endif

namespace ledcube {

namespace charmap {

//(
const unsigned char _c28[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..##."
	".#..."
	".#..."
	".#..."
	"..##."
, PROTECT({0x32, 0x10, 0x83, 0x00}) );
//)
const unsigned char _c29[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"...#."
	"...#."
	"...#."
	".##.."
, PROTECT({0x60, 0x84, 0x26, 0x00}) );
//[
const unsigned char _c5b[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"###.."
	"#...."
	"#...."
	"#...."
	"###.."
, PROTECT({0xe4, 0x21, 0x0e, 0x00}) );
//]
const unsigned char _c5d[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..###"
	"....#"
	"....#"
	"....#"
	"..###"
, PROTECT({0x38, 0x42, 0x13, 0x80}) );
//{
const unsigned char _c7b[] PROGMEM_ENABLED =
CHARMAP_DATA(
	"..##."
	".#..."
	"##..."
	".#..."
	"..##."
, PROTECT({0x32, 0x30, 0x83, 0x00}) );
//}
const unsigned char _c7d[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"...#."
	"...##"
	"...#."
	".##.."
, PROTECT({0x60, 0x86, 0x26, 0x00}) );

} //namespace ledcube

} //namespace charmap

#endif //ndef __CHM_PAREN_H
