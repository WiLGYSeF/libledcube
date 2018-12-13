#ifndef __CHM_SHAPE_H
#define __CHM_SHAPE_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

const char _chm_heart[] =
	".#.#."
	"#####"
	"#####"
	".###."
	"..#.."
;

const char _chm_smileyface[] =
	"##.##"
	"##.##"
	"....."
	"#...#"
	".###."
;

const char _chm_star[] =
	"....."
	"..#.."
	"#####"
	".###."
	"#...#"
;

#endif //ndef __CHM_SHAPE_H
