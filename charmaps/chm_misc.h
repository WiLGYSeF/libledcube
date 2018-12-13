#ifndef __CHM_MISC_H
#define __CHM_MISC_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//#
const unsigned char _c23[] =
CHARMAP_DATA(
	".#.#."
	"#####"
	".#.#."
	"#####"
	".#.#."
, PROTECT({0x57, 0xd5, 0xf5, 0x00}) );
//$
const unsigned char _c24[] =
CHARMAP_DATA(
	".####"
	"#.#.."
	".###."
	"..#.#"
	"####."
, PROTECT({0x7d, 0x1c, 0x5f, 0x00}) );
//%
const unsigned char _c25[] =
CHARMAP_DATA(
	"##..#"
	"##.#."
	"..#.."
	".#.##"
	"#..##"
, PROTECT({0xce, 0x88, 0xb9, 0x80}) );
//&
const unsigned char _c26[] =
CHARMAP_DATA(
	".##.."
	"#.#.."
	".##.."
	"#.#.."
	".###."
, PROTECT({0x65, 0x19, 0x47, 0x00}) );
//*
const unsigned char _c2a[] =
CHARMAP_DATA(
	"..#.."
	"#.#.#"
	".###."
	"#.#.#"
	"..#.."
, PROTECT({0x25, 0x5d, 0x52, 0x00}) );
//+
const unsigned char _c2b[] =
CHARMAP_DATA(
	"..#.."
	"..#.."
	"#####"
	"..#.."
	"..#.."
, PROTECT({0x21, 0x3e, 0x42, 0x00}) );
//-
const unsigned char _c2d[] =
CHARMAP_DATA(
	"....."
	"....."
	"####."
	"....."
	"....."
, PROTECT({0x00, 0x3c, 0x00, 0x00}) );
///
const unsigned char _c2f[] =
CHARMAP_DATA(
	"....#"
	"...#."
	"..#.."
	".#..."
	"#...."
, PROTECT({0x08, 0x88, 0x88, 0x00}) );
//<
const unsigned char _c3c[] =
CHARMAP_DATA(
	"....."
	"..#.."
	".#..."
	"..#.."
	"....."
, PROTECT({0x01, 0x10, 0x40, 0x00}) );
//=
const unsigned char _c3d[] =
CHARMAP_DATA(
	"....."
	"####."
	"....."
	"####."
	"....."
, PROTECT({0x07, 0x81, 0xe0, 0x00}) );
//>
const unsigned char _c3e[] =
CHARMAP_DATA(
	"....."
	"..#.."
	"...#."
	"..#.."
	"....."
, PROTECT({0x01, 0x04, 0x40, 0x00}) );
//@
const unsigned char _c40[] =
CHARMAP_DATA(
	".###."
	"#.#.#"
	"#.###"
	"#...."
	".####"
, PROTECT({0x75, 0x6f, 0x07, 0x80}) );
//\.
const unsigned char _c5c[] =
CHARMAP_DATA(
	"#...."
	".#..."
	"..#.."
	"...#."
	"....#"
, PROTECT({0x82, 0x08, 0x20, 0x80}) );
//^
const unsigned char _c5e[] =
CHARMAP_DATA(
	"..#.."
	".#.#."
	"....."
	"....."
	"....."
, PROTECT({0x22, 0x80, 0x00, 0x00}) );
//_
const unsigned char _c5f[] =
CHARMAP_DATA(
	"....."
	"....."
	"....."
	"....."
	"#####"
, PROTECT({0x00, 0x00, 0x0f, 0x80}) );
//`
const unsigned char _c60[] =
CHARMAP_DATA(
	".#..."
	"..#.."
	"....."
	"....."
	"....."
, PROTECT({0x41, 0x00, 0x00, 0x00}) );
//|
const unsigned char _c7c[] =
CHARMAP_DATA(
	"..#.."
	"..#.."
	"..#.."
	"..#.."
	"..#.."
, PROTECT({0x21, 0x08, 0x42, 0x00}) );
//~
const unsigned char _c7e[] =
CHARMAP_DATA(
	"....."
	"##..."
	"..##."
	"....."
	"....."
, PROTECT({0x06, 0x0c, 0x00, 0x00}) );

#endif //ndef __CHM_MISC_H
