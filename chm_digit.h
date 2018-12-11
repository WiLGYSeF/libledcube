#ifndef __CHM_DIGIT_H
#define __CHM_DIGIT_H

#include "cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//0
const char _c30[] =
	".###."
	"#..##"
	"#.#.#"
	"##..#"
	".###."
;
//1
const char _c31[] =
	".##.."
	"..#.."
	"..#.."
	"..#.."
	".###."
;
//2
const char _c32[] =
	".##.."
	"#..#."
	"..#.."
	".#..."
	"####."
;
//3
const char _c33[] =
	"###.."
	"...#."
	".##.."
	"...#."
	"####."
;
//4
const char _c34[] =
	"#..#."
	"#..#."
	"####."
	"...#."
	"...#."
;
//5
const char _c35[] =
	"####."
	"#...."
	"###.."
	"...#."
	"###.."
;
//6
const char _c36[] =
	".##.."
	"#...."
	"###.."
	"#..#."
	".##.."
;
//7
const char _c37[] =
	"####."
	"...#."
	"..#.."
	".#..."
	"#...."
;
//8
const char _c38[] =
	".##.."
	"#..#."
	".##.."
	"#..#."
	".##.."
;
//9
const char _c39[] =
	".##.."
	"#..#."
	".###."
	"...#."
	"...#."
;

#endif //ndef __CHM_DIGIT_H
