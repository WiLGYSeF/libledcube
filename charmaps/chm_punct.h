#ifndef __CHM_PUNCT_H
#define __CHM_PUNCT_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//
const char _c20[] =
	"....."
	"....."
	"....."
	"....."
	"....."
;
//!
const char _c21[] =
	"..#.."
	"..#.."
	"..#.."
	"....."
	"..#.."
;
//"
const char _c22[] =
	"..##."
	"..##."
	"....."
	"....."
	"....."
;
//'
const char _c27[] =
	"..#.."
	"..#.."
	"....."
	"....."
	"....."
;
//,
const char _c2c[] =
	"....."
	"....."
	"..##."
	"...#."
	"..#.."
;
//.
const char _c2e[] =
	"....."
	"....."
	"....."
	"..##."
	"..##."
;
//:
const char _c3a[] =
	"..#.."
	"..#.."
	"....."
	"..#.."
	"..#.."
;
//;
const char _c3b[] =
	"..#.."
	"..#.."
	"....."
	"...#."
	"..#.."
;
//?
const char _c3f[] =
	".##.."
	"#..#."
	"...#."
	"..#.."
	"..#.."
;

#endif //ndef __CHM_PUNCT_H
