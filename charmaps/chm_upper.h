#ifndef __CHM_UPPER_H
#define __CHM_UPPER_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//A
const unsigned char _c41[] =
CHARMAP_DATA(
	".##.."
	"#..#."
	"####."
	"#..#."
	"#..#."
, PROTECT({0x64, 0xbd, 0x29, 0x00}) );
//B
const unsigned char _c42[] =
CHARMAP_DATA(
	"###.."
	"#..#."
	"###.."
	"#..#."
	"###.."
, PROTECT({0xe4, 0xb9, 0x2e, 0x00}) );
//C
const unsigned char _c43[] =
CHARMAP_DATA(
	".###."
	"#...."
	"#...."
	"#...."
	".###."
, PROTECT({0x74, 0x21, 0x07, 0x00}) );
//D
const unsigned char _c44[] =
CHARMAP_DATA(
	"###.."
	"#..#."
	"#..#."
	"#..#."
	"###.."
, PROTECT({0xe4, 0xa5, 0x2e, 0x00}) );
//E
const unsigned char _c45[] =
CHARMAP_DATA(
	"####."
	"#...."
	"###.."
	"#...."
	"####."
, PROTECT({0xf4, 0x39, 0x0f, 0x00}) );
//F
const unsigned char _c46[] =
CHARMAP_DATA(
	"####."
	"#...."
	"###.."
	"#...."
	"#...."
, PROTECT({0xf4, 0x39, 0x08, 0x00}) );
//G
const unsigned char _c47[] =
CHARMAP_DATA(
	".###."
	"#...."
	"#.##."
	"#..#."
	".###."
, PROTECT({0x74, 0x2d, 0x27, 0x00}) );
//H
const unsigned char _c48[] =
CHARMAP_DATA(
	"#..#."
	"#..#."
	"####."
	"#..#."
	"#..#."
, PROTECT({0x94, 0xbd, 0x29, 0x00}) );
//I
const unsigned char _c49[] =
CHARMAP_DATA(
	".###."
	"..#.."
	"..#.."
	"..#.."
	".###."
, PROTECT({0x71, 0x08, 0x47, 0x00}) );
//J
const unsigned char _c4a[] =
CHARMAP_DATA(
	"####."
	"..#.."
	"..#.."
	"..#.."
	"##..."
, PROTECT({0xf1, 0x08, 0x4c, 0x00}) );
//K
const unsigned char _c4b[] =
CHARMAP_DATA(
	"#..#."
	"#.#.."
	"##..."
	"#.#.."
	"#..#."
, PROTECT({0x95, 0x31, 0x49, 0x00}) );
//L
const unsigned char _c4c[] =
CHARMAP_DATA(
	"#...."
	"#...."
	"#...."
	"#...."
	"####."
, PROTECT({0x84, 0x21, 0x0f, 0x00}) );
//M
const unsigned char _c4d[] =
CHARMAP_DATA(
	"#...#"
	"##.##"
	"#.#.#"
	"#...#"
	"#...#"
, PROTECT({0x8e, 0xeb, 0x18, 0x80}) );
//N
const unsigned char _c4e[] =
CHARMAP_DATA(
	"#..#."
	"##.#."
	"#.##."
	"#..#."
	"#..#."
, PROTECT({0x96, 0xad, 0x29, 0x00}) );
//O
const unsigned char _c4f[] =
CHARMAP_DATA(
	".##.."
	"#..#."
	"#..#."
	"#..#."
	".##.."
, PROTECT({0x64, 0xa5, 0x26, 0x00}) );
//P
const unsigned char _c50[] =
CHARMAP_DATA(
	"###.."
	"#..#."
	"###.."
	"#...."
	"#...."
, PROTECT({0xe4, 0xb9, 0x08, 0x00}) );
//Q
const unsigned char _c51[] =
CHARMAP_DATA(
	".###."
	"#...#"
	"#.#.#"
	"#..#."
	".##.#"
, PROTECT({0x74, 0x6b, 0x26, 0x80}) );
//R
const unsigned char _c52[] =
CHARMAP_DATA(
	"###.."
	"#..#."
	"###.."
	"#.#.."
	"#..#."
, PROTECT({0xe4, 0xb9, 0x49, 0x00}) );
//S
const unsigned char _c53[] =
CHARMAP_DATA(
	".###."
	"#...."
	".##.."
	"...#."
	"###.."
, PROTECT({0x74, 0x18, 0x2e, 0x00}) );
//T
const unsigned char _c54[] =
CHARMAP_DATA(
	".###."
	"..#.."
	"..#.."
	"..#.."
	"..#.."
, PROTECT({0x71, 0x08, 0x42, 0x00}) );
//U
const unsigned char _c55[] =
CHARMAP_DATA(
	"#..#."
	"#..#."
	"#..#."
	"#..#."
	".##.."
, PROTECT({0x94, 0xa5, 0x26, 0x00}) );
//V
const unsigned char _c56[] =
CHARMAP_DATA(
	"#.#.."
	"#.#.."
	"#.#.."
	"#.#.."
	".#..."
, PROTECT({0xa5, 0x29, 0x44, 0x00}) );
//W
const unsigned char _c57[] =
CHARMAP_DATA(
	"#...#"
	"#...#"
	"#.#.#"
	"##.##"
	"#...#"
, PROTECT({0x8c, 0x6b, 0xb8, 0x80}) );
//X
const unsigned char _c58[] =
CHARMAP_DATA(
	"#...#"
	".#.#."
	"..#.."
	".#.#."
	"#...#"
, PROTECT({0x8a, 0x88, 0xa8, 0x80}) );
//Y
const unsigned char _c59[] =
CHARMAP_DATA(
	"#...#"
	"#...#"
	".#.#."
	"..#.."
	"..#.."
, PROTECT({0x8c, 0x54, 0x42, 0x00}) );
//Z
const unsigned char _c5a[] =
CHARMAP_DATA(
	"####."
	"...#."
	"..#.."
	".#..."
	"####."
, PROTECT({0xf0, 0x88, 0x8f, 0x00}) );

#endif //ndef __CHM_UPPER_H
