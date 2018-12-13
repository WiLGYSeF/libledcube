#ifndef __CHM_PAREN_H
#define __CHM_PAREN_H

#include "../cubehead.h"

#if CUBE_WIDTH != 5
	#warning "Cube character maps are designed for width of 5"
#endif

//(
const char _c28[] =
	"..##."
	".#..."
	".#..."
	".#..."
	"..##."
;
//)
const char _c29[] =
	".##.."
	"...#."
	"...#."
	"...#."
	".##.."
;
//[
const char _c5b[] =
	"###.."
	"#...."
	"#...."
	"#...."
	"###.."
;
//]
const char _c5d[] =
	"..###"
	"....#"
	"....#"
	"....#"
	"..###"
;
//{
const char _c7b[] =
	"..##."
	".#..."
	"##..."
	".#..."
	"..##."
;
//}
const char _c7d[] =
	".##.."
	"...#."
	"...##"
	"...#."
	".##.."
;

#endif //ndef __CHM_PAREN_H
