#ifndef __CHM_LOWER_H
#define __CHM_LOWER_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//a
const unsigned char _c61[] =
CHARMAP_DATA(
	"....."
	".##.."
	"#..#."
	"#..#."
	".####"
, PROTECT({0x03, 0x25, 0x27, 0x80}) );
//b
const unsigned char _c62[] =
CHARMAP_DATA(
	"#...."
	"#...."
	"##..."
	"#.#.."
	"##..."
, PROTECT({0x84, 0x31, 0x4c, 0x00}) );
//c
const unsigned char _c63[] =
CHARMAP_DATA(
	"....."
	".##.."
	"#...."
	"#...."
	".##.."
, PROTECT({0x03, 0x21, 0x06, 0x00}) );
//d
const unsigned char _c64[] =
CHARMAP_DATA(
	"..#.."
	"..#.."
	".##.."
	"#.#.."
	".##.."
, PROTECT({0x21, 0x19, 0x46, 0x00}) );
//e
const unsigned char _c65[] =
CHARMAP_DATA(
	".##.."
	"#..#."
	"####."
	"#...."
	".###."
, PROTECT({0x64, 0xbd, 0x07, 0x00}) );
//f
const unsigned char _c66[] =
CHARMAP_DATA(
	".###."
	"#...."
	"###.."
	"#...."
	"#...."
, PROTECT({0x74, 0x39, 0x08, 0x00}) );
//g
const unsigned char _c67[] =
CHARMAP_DATA(
	"..##."
	".#..#"
	"..###"
	"....#"
	"..##."
, PROTECT({0x32, 0x4e, 0x13, 0x00}) );
//h
const unsigned char _c68[] =
CHARMAP_DATA(
	"#...."
	"#...."
	"##..."
	"#.#.."
	"#.#.."
, PROTECT({0x84, 0x31, 0x4a, 0x00}) );
//i
const unsigned char _c69[] =
CHARMAP_DATA(
	"..#.."
	"....."
	"..#.."
	"..#.."
	"..#.."
, PROTECT({0x20, 0x08, 0x42, 0x00}) );
//j
const unsigned char _c6a[] =
CHARMAP_DATA(
	"..#.."
	"....."
	"..#.."
	"..#.."
	"##..."
, PROTECT({0x20, 0x08, 0x4c, 0x00}) );
//k
const unsigned char _c6b[] =
CHARMAP_DATA(
	"#...."
	"#...."
	"#.#.."
	"##..."
	"#.#.."
, PROTECT({0x84, 0x29, 0x8a, 0x00}) );
//l
const unsigned char _c6c[] =
CHARMAP_DATA(
	".#..."
	".#..."
	".#..."
	".#..."
	"..##."
, PROTECT({0x42, 0x10, 0x83, 0x00}) );
//m
const unsigned char _c6d[] =
CHARMAP_DATA(
	"....."
	"....."
	".#.#."
	"#.#.#"
	"#...#"
, PROTECT({0x00, 0x15, 0x58, 0x80}) );
//n
const unsigned char _c6e[] =
CHARMAP_DATA(
	"....."
	"....."
	"##..."
	"#.#.."
	"#.#.."
, PROTECT({0x00, 0x31, 0x4a, 0x00}) );
//o
const unsigned char _c6f[] =
CHARMAP_DATA(
	"....."
	".##.."
	"#..#."
	"#..#."
	".##.."
, PROTECT({0x03, 0x25, 0x26, 0x00}) );
//p
const unsigned char _c70[] =
CHARMAP_DATA(
	"###.."
	"#..#."
	"###.."
	"#...."
	"#...."
, PROTECT({0xe4, 0xb9, 0x08, 0x00}) );
//q
const unsigned char _c71[] =
CHARMAP_DATA(
	".##.."
	"#..#."
	".###."
	"...#."
	"...##"
, PROTECT({0x64, 0x9c, 0x21, 0x80}) );
//r
const unsigned char _c72[] =
CHARMAP_DATA(
	"....."
	"....."
	"..##."
	".#..."
	".#..."
, PROTECT({0x00, 0x0c, 0x84, 0x00}) );
//s
const unsigned char _c73[] =
CHARMAP_DATA(
	".###."
	"#...."
	".##.."
	"...#."
	"###.."
, PROTECT({0x74, 0x18, 0x2e, 0x00}) );
//t
const unsigned char _c74[] =
CHARMAP_DATA(
	"....."
	"..#.."
	".###."
	"..#.."
	"..#.."
, PROTECT({0x01, 0x1c, 0x42, 0x00}) );
//u
const unsigned char _c75[] =
CHARMAP_DATA(
	"....."
	"....."
	"#..#."
	"#..#."
	".##.."
, PROTECT({0x00, 0x25, 0x26, 0x00}) );
//v
const unsigned char _c76[] =
CHARMAP_DATA(
	"....."
	"....."
	"#.#.."
	"#.#.."
	".#..."
, PROTECT({0x00, 0x29, 0x44, 0x00}) );
//w
const unsigned char _c77[] =
CHARMAP_DATA(
	"....."
	"....."
	"#...#"
	"#.#.#"
	".#.#."
, PROTECT({0x00, 0x23, 0x55, 0x00}) );
//x
const unsigned char _c78[] =
CHARMAP_DATA(
	"....."
	"#..#."
	".##.."
	".##.."
	"#..#."
, PROTECT({0x04, 0x98, 0xc9, 0x00}) );
//y
const unsigned char _c79[] =
CHARMAP_DATA(
	"....."
	"#..#."
	".##.."
	".#..."
	"#...."
, PROTECT({0x04, 0x98, 0x88, 0x00}) );
//z
const unsigned char _c7a[] =
CHARMAP_DATA(
	"....."
	"####."
	"..#.."
	".#..."
	"####."
, PROTECT({0x07, 0x88, 0x8f, 0x00}) );

#endif //ndef __CHM_LOWER_H
