# libledcube
### Table of Contents:
- [Making the Library](#making-the-library)
- [Installing the Library](#installing-the-library)
- [Cube Formatting](#cube-formatting)
- [Library Documentation](#library-documentation)
- [Preprocessor Directives](#preprocessor-directives)
- [Function Documentation](#function-documentation)
  - [cubemap.h](#cubemaph)
  - [charmap.h](#charmaph)
  - [pattern.h](#patternh)
- [Character Maps](#character-maps)

---

A general library for controlling LED cubes with shift registers.
Click [here](https://www.wilgysef.com/5x5x5-led-cube/) to see a video of a LED cube using libledcube.

Example Schematic: ![Example Schematic](https://www.wilgysef.com/5x5x5-led-cube/schematic.png)
Go to [this page](https://www.wilgysef.com/5x5x5-led-cube/#hdr-schematic) to read more about the schematic and how the LED cube functions.

# Making the Library
To recompile the library after making changes, use:
```bash
make
```

# Installing the Library
The library can be installed easily on Linux machines by using:
```bash
make zip
make install
```

The library can then be used by
```c++
#include <libledcube.h>
```

# Cube Formatting
This is the bitmap formatting for a 5x5x5 LED cube:
The columns fron a top-down view are numbered as so:
```
20 21 22 23 24
15 16 17 18 19
10 11 12 13 14
 5  6  7  8  9
 0  1  2  3  4
```
where `0` is the front-left column.

The axes are:
x: left `0` &#8594; right `n`
y: top: `0` &#8594; down `n`
z: front `0` &#8594; back `n`
Which makes the front-top-left voxel as `(0, 0, 0)`.

Columns are stored as bits in an array in this order for a 5x5x5:
`7  6  5: 4  3  2  1  0    15:14 13 12 11 10: 9  8    23 22 21 20:19 18 17 16     -  -  -  -  -  -  - 24`
The colons denote a change in z-axis, and the dashes denote unused bits.

# Library Documentation
All functions/classes are declared in the namespace `ledcube`.
Not all features are documented, only the functions and most-used.
Please see the `*.h` files for more.

# Preprocessor Directives
Some library configuration is in the form of preprocessor macros.
They can be changed in `cubehead.h`.
Pin numbers can be changed in `pins.h`.

## \#define CUBE_WIDTH [value]
Sets the cube's dimensions
- value - cube width (min 3, max 255)
Default 5.

## \#define CHARMAP_COMPRESS
If defined, uses the compressed version of charmaps ([see below](#character-maps)).
Default enabled for Arduino mode only.

## \#define DIGITALWRITE_FAST
If defined, use the *digitalWriteFast* function.
Arduino does not have this feature by default, but Teensy does.
Default disabled.

## \#define CUBE_CURFRAME
If defined, a variable `ledcube::g_curframe` will be defined.
It stores the cube frame that was last drawn to the cube.
Default disabled.

## \#define PATTERN_KILLFLAG
If defined, a variable `ledcube::g_patternKillFlag` will be defined.
It allows the program to cancel any `pattern::*` patterns midway by setting `ledcube::g_patternKillFlag` to 1.
Default enabled for Arduino mode only.

## \#define USE_PROGMEM
If defined, charmaps will use PROGMEM ([see below](#character-maps)).
Default enabled for Arduino mode only.

## \#define USE_SPI_SHIFTOUT
If defined, drawing each frame will use SPI instead of manually bit-banging.
This feature has not yet been tested!
Default disabled.

# Function Documentation
# cubemap.h

## Cubeframe()
creates an empty cube frame

**Parameters**
none

## Cubeframe(uint16_t delay)
creates an empty cube frame with a display delay

**Parameters**
- delay  - display delay in milliseconds

## static cubecol Cubeframe::xz_to_col(uint8_t x, uint8_t z)
converts an xz coordinate to a column number

**Parameters**
- x - x coordinate
- z - z coordinate

**Returns**
number of column

## static uint16_t Cubeframe::col_to_xz(cubecol col)
converts a column number to xz coordinate

**Parameters**
- col - column number

**Returns**
returns (x << 8) | z

## static cubevol Cubeframe::xyz_to_vox(uint8_t x, uint8_t y, uint8_t z)
converts xyz coordinate to a voxel number

**Parameters**
- x - x coordinate
- y - y coordinate
- z - z coordinate

**Returns**
returns a voxel number

## static uint32_t Cubeframe::vox_to_xyz(cubevol v)
converts a voxel number to xyz coordinate

**Parameters**
- v - voxel number

**Returns**
returns (x << 16) | (y << 8) | z

## static uint8_t Cubeframe::get_col(const cubelvl level, cubecol col)
gets the bit value of the column on the specified level

**Parameters**
- level - a level of the cube
- col - the column number

**Returns**
returns 1 for on, 0 for off

## static uint8_t Cubeframe::get_xz(const cubelvl level, uint8_t x, uint8_t z)
gets the bit value of the xz coordinate on *level*

**Parameters**
- level - a level of the cube
- x - x coordinate
- z - z coordinate

**Returns**
returns 1 for on, 0 for off

## uint8_t Cubeframe get_voxel(uint8_t x, uint8_t y, uint8_t z) const
gets the bit value of the xyz coordinate

**Parameters**
- x - x coordinate
- y - y coordinate
- z - z coordinate

**Returns**
returns 1 for on, 0 for off

## static void Cubeframe::set_col(cubelvl level, uint8_t led_on, cubecol col)
sets the bit of the column on *level*

**Parameters**
- level - a level of the cube
- led_on - 1 to set the column on, 0 to set the column off
- col - the column number

## static void Cubeframe::set_xz(cubelvl level, uint8_t led_on, uint8_t x, uint8_t z)
sets the bit of the xz coordinate on *level*

**Parameters**
- level - a level of the cube
- led_on - 1 to set the column on, 0 to set the column off
- x - x coordinate
- z - z coordinate

## void Cubeframe::set_voxel(uint8_t led_on, uint8_t x, uint8_t y, uint8_t z)
sets the bit of the xyz coordinate

**Parameters**
- led_on - 1 to set the column on, 0 to set the column off
- x - x coordinate
- y - y coordinate
- z - z coordinate

## void Cubeframe::set_level(uint8_t led_on, uint8_t y)
sets the bits on the entire *y* level

**Parameters**
- led_on - 1 to set the level on, 0 to set the level off
- y - y coordinate

## void Cubeframe::set(uint8_t led_on)
sets the bits on the entire frame

**Parameters**
- led_on - 1 to set the frame on, 0 to set the frame off

## void Cubeframe::xrow(uint8_t led_on, uint8_t x, uint8_t y)
sets the bits of the z-coordinates on xy

**Paramters**
- led_on - 1 to set the z-coordinates on, 0 to set the z-coordinates off
- x - x coordinate
- y - y coordinate

## void Cubeframe::yrow(uint8_t led_on, uint8_t x, uint8_t z)
sets the bits of the y-coordinates on xz

**Paramters**
- led_on - 1 to set the y-coordinates on, 0 to set the y-coordinates off
- x - x coordinate
- z - z coordinate

## void Cubeframe::zrow(uint8_t led_on, uint8_t y, uint8_t z)
sets the bits of the x-coordinates on yz

**Paramters**
- led_on - 1 to set the x-coordinates on, 0 to set the x-coordinates off
- y - y coordinate
- z - z coordinate

## void Cubeframe::get_xplane(cubelvl plane, uint8_t x) const
gets the x-plane at *x* and stores it in *plane*

**Parameters**
- plane - the cubelvl plane where the bits are stored
- x - x coordinate

## void Cubeframe::get_yplane(cubelvl plane, uint8_t y) const
gets the y-plane at *y* and stores it in *plane*

**Parameters**
- plane - the cubelvl plane where the bits are stored
- y - y coordinate

## void Cubeframe::get_zplane(cubelvl plane, uint8_t z) const
gets the z-plane at *z* and stores it in *plane*

**Parameters**
- plane - the cubelvl plane where the bits are stored
- z - z coordinate

## void Cubeframe::set_xplane(const cubelvl plane, uint8_t x)
sets the x-plane at *x* using the bit information from *plane*

**Parameters**
- plane - the cubelvl plane where the bits are stored
- x - x coordinate

## void Cubeframe::set_yplane(const cubelvl plane, uint8_t y)
sets the y-plane at *y* using the bit information from *plane*

**Parameters**
- plane - the cubelvl plane where the bits are stored
- y - y coordinate

## void Cubeframe::set_zplane(const cubelvl plane, uint8_t z)
sets the z-plane at *z* using the bit information from *plane*

**Parameters**
- plane - the cubelvl plane where the bits are stored
- z - z coordinate

## void Cubeframe::xplane(uint8_t led_on, uint8_t x)
sets the bits on the x-plane *x*

**Parameters**
- led_on - 1 to set the x-plane on, 0 to set the x-plane off
- x - x coordinate

## void Cubeframe::yplane(uint8_t led_on, uint8_t y)
sets the bits on the y-plane *y*

**Parameters**
- led_on - 1 to set the y-plane on, 0 to set the y-plane off
- y - y coordinate

## void Cubeframe::zplane(uint8_t led_on, uint8_t z)
sets the bits on the z-plane *z*

**Parameters**
- led_on - 1 to set the z-plane on, 0 to set the z-plane off
- z - z coordinate

## void Cubeframe::shift_plane(uint8_t axisdir)
shifts the planes on the cube on the axis and direction

**Parameters**
- axisdir - axis and direction specified by AXISDIR(A, D) macro
  - AXIS_X, AXIS_Y, AXIS_Z
  - DIR_FORWARD, DIR_BACKWARD

## static void Cubeframe::reverse_plane(cubelvl plane, uint8_t dir)
reverses *plane* by a direction

**Parameters**
- plane - the cubelvl plane where the bits are stored
- dir - direction specified by macro
  - DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT

## static void Cubeframe::rotate_plane(cubelvl plane, uint8_t times)
rotates *plane* counter-clockwise *n* times

**Parameters**
- plane - the cubelvl plane where the bits are stored
- times - how many times to rotate the plane counter-clockwise

## void Cubeframe::draw_level(uint8_t y) const
sends the frame level bit information to the shift registers and draws it.
if not running on Arduino, does nothing.

**Parameters**
- y - y coordinate

## void Cubeframe::draw_frame() const
sends the frame bit information to the shift registers and draws it.
if not running on Arduino, prints to stdout.

## static void Cubeframe::delay_frame(uint16_t delayms)
delays the cube frame animation, keeping the current frame drawn.
if not running on Arduino, only delays.

**Parameters**
- delayms - how long to delay the currently drawn frame in milliseconds

## static void Cubeframe::print_plane(const cubelvl plane, uint8_t multilevel)
prints *plane* to stdout

**Parameters**
- plane - the cubelvl plane where the bits are stored
- multilevel - if non-zero, prints ` ` between rows, else prints `\n`

## void Cubeframe::print_frame() const
prints the cube frame information to stdout.
if `g_verboseprint` is set, it also draws coordinates alongside the frame.

## void setup_SPI()
sets up SPI mode, only if `#USE_SPI` is defined

# charmap.h
## void charmap::buildframe(Cubeframe &fr, const unsigned char *ascii, uint16_t delay)
builds a cube frame of the character map *ascii*

**Parameters**
- fr - reference to cube frame to build on
- ascii - pointer to one-dimensional charmap
- delay - frame delay in milliseconds

## Cubeframe *charmap::buildstr(const char *str, size_t *count, uint16_t delay, bool startblank)
builds a cube frame array of character maps from *str*

**Parameters**
- str - string of characters to map
- count - the function sets this to the length of the returned cube frame array
- delay - the delay for each frame in milliseconds
- startblank - the cube frame array starts with an empty frame

**Returns**
returns a cube frame array with character maps of size *count*.
returns NULL on failure.

## void charmap::scrolltext(const Cubeframe *frames, size_t count, uint8_t direction, size_t spacing)
draws scrolling text on the cube using the *frames* cube frame array

**Parameters**
- frames - cube frame array to animate/draw with
- count - the length of the cube frame array
- direction - direction specified by macro
  - DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
- spacing - voxel width spacing between characters displayed

# pattern.h
## void pattern::alternate_full(Cubeframe &fr, uint8_t zero_on)
sets a pattern on *fr* with alternating on/off voxels (single-frame pattern)

**Parameters**
- fr - reference to cube frame
- zero_on - should `(0, 0, 0)` start off as on

## void pattern::border(Cubeframe &fr, uint8_t led_on, uint8_t width)
sets the voxels on/off around the centered border on *fr* (single-frame pattern)

**Parameters**
- fr - reference to cube frame
- led_on - 1 to set the border on, 0 to set the border off
- width - width of border that will be drawn around center

## void pattern::random(Cubeframe &fr)
randomly set voxels on/off (single-frame pattern)

**Paramters**
- fr - reference to cube frame

## void pattern::random_modify(Cubeframe &fr, Cubeframe &ref, size_t count)
randomly change *n* voxel states on unique coordinates (single-frame pattern)

**Parameters**
- fr - reference to cube frame
- ref - reference to a cube frame the pattern uses as reference to change voxels
- count - how many voxel states to change

## void pattern::border_bounce(size_t count, uint16_t delay)
draws an animation of expanding/contracting border

**Parameters**
- count - how many times to expand/contract
- delay - frame delay in milliseconds

## void pattern::border_spin(uint8_t clockwise, cubeperim voxelperlevel, size_t count, uint16_t delay)
draws an animation of spinning randomly set voxels around the border

**Parameters**
- clockwise - if non-zero, spin clockwise, otherwise spin counter-clockwise
- voxelperlevel - how many voxels to set on the border per level
- count - how many frames to spin the pattern for
- delay - frame delay in milliseconds

## void pattern::firework(uint16_t launchdelay, uint16_t explosiondelay)
draws an animation of a single, randomly-placed firework

**Parameters**
- launchdelay - frame delay in milliseconds during launch
- explosiondelay - frame delay in milliseconds after explosion

## void pattern:plane_bounce(size_t count, uint16_t delay)
draws an animation of bouncing a plane between random edges

**Parameters**
- count - how many times to bounce
- delay - frame delay in milliseconds

## void pattern::rain(size_t count, uint16_t delay)
draws an animation of raindrops

**Parameters**
- count - how many raindrops to draw
- delay - frame delay in milliseconds

## void pattern::random_set(uint8_t led_on, uint16_t delay)
draws an animation of setting random voxels on/off until all are on/off

**Parameters**
- led_on - 1 to set voxels on, 0 to set voxels off
- delay - frame delay in milliseconds

## void pattern::send_voxel(uint8_t axis, size_t count, uint16_t delay, uint16_t leveldelay)
draws an animation of sending random voxels across the cube between edges

**Parameters**
- axis - axis specified by macro
  - AXIS_X, AXIS_Y, AXIS_Z
- count - how many voxels to send over
- delay - frame delay in milliseconds for the voxel travel
- leveldelay - frame delay in milliseconds for between each voxel send

## void pattern::stream(uint8_t axdir, size_t count, size_t spacing, uint16_t delay)
draws an animation of a stream of voxels traveling from one edge to the other

**Parameters**
- axdir - axis and direction specified by AXISDIR(A, D) macro
  - AXIS_X, AXIS_Y, AXIS_Z
  - DIR_FORWARD, DIR_BACKWARD
- count - how many voxels in the stream
- spacing - spacing between each voxel
- delay - frame delay in milliseconds

# Character Maps
Character maps are arrays of data that represent images characters drawn with voxels on the cube. Character maps can be drawn using the `charmap::*` functions.
The library comes with these built-in maps in `charmaps/chm_*.h` as examples that are designed for cube widths of 5. For example, the charmap for `A` with a width of 5 is given as:
```c++
const unsigned char _c41[] PROGMEM_ENABLED =
CHARMAP_DATA(
	".##.."
	"#..#."
	"####."
	"#..#."
	"#..#."
, PROTECT({0x64, 0xbd, 0x29, 0x00}) );
```

There are two forms of character maps: uncompressed and compressed.
The pattern made with `#` and `.` are uncompressed, representing 1 and 0 bits for the frame, respectively. It is the simple, visual way to store any custom charmaps for the program. However, this approach uses 8 times as much memory as necessary, and on small microcontrollers, this is an issue.

If `CHARMAP_COMPRESSED` is defined, as described above in the Preprocessor Directives section, then it will use the compressed form. For `A` with a width of 5, this is:
```c++
{0x64, 0xbd, 0x29, 0x00}
```
Note that the `PROTECT` macro is only used to ensure proper functionality of the `CHARMAP_DATA(U, C)` macro, which will either be processed as `U` or `C`, depending on whether `CHARMAP_COMPRESSED` is defined.

If `USE_PROGMEM` is defined, as described above, then the character maps will be stored in flash program memory.

To make your own compressed versions of the charmaps, use `compress-charmap.py` included with the library.

To compress the pattern for `A`, use:
```bash
python3 compress-charmap.py ".##..#..#.####.#..#.#..#."
```
which will result in
```c++
{0x64, 0xbd, 0x29, 0x00}
```

To decompress, use:
```bash
python3 compress-charmap.py --decompress 5 --newline "{0x64, 0xbd, 0x29, 0x00}"
```
which will result in
```c++
".##.."
"#..#."
"####."
"#..#."
"#..#."
```
