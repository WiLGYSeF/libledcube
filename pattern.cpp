#include "pattern.h"
#include <stdlib.h>
#include <string.h>
#include "voxellist.h"

namespace ledcube {

namespace pattern {

//=====================
//single-frame patterns
//=====================

//alternate between on/off voxels
void alternate_full(Cubeframe &fr, uint8_t zero_on)
{
	uint8_t patt = zero_on ? 0x55 : 0xaa;

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
	#if CUBE_WIDTH & 1
		memset(fr.levels[y], patt, CUBELVL_SIZE);
	#else
		memset(fr.levels[y], (y & 1) ? patt : ~patt, CUBELVL_SIZE);
	#endif

		patt = ~patt;
	}
}

//creates a cube border of specified width
void border(Cubeframe &fr, uint8_t led_on, uint8_t width)
{
	uint8_t off = (CUBE_WIDTH - width) / 2;
	width--;

	if(!width)
	{
		uint8_t h = CUBE_WIDTH / 2;
		fr.set_voxel(led_on, h, h, h);
		return;
	}

	if(width >= CUBE_WIDTH)
	{
		off = 0;
		width = CUBE_WIDTH - 1;
	}

	uint8_t offwi = off + width;

	for (uint8_t i = 0; i <= width; i++)
	{
		//x-constant/perpendicular lines
		fr.set_voxel(led_on, off, off, off + i);
		fr.set_voxel(led_on, off, offwi, off + i);
		fr.set_voxel(led_on, offwi, off, off + i);
		fr.set_voxel(led_on, offwi, offwi, off + i);

		//y-constant/perpendicular lines
		fr.set_voxel(led_on, off, off + i, off);
		fr.set_voxel(led_on, off, off + i, offwi);
		fr.set_voxel(led_on, offwi, off + i, off);
		fr.set_voxel(led_on, offwi, off + i, offwi);

		//z-constant/perpendicular lines
		fr.set_voxel(led_on, off + i, off, off);
		fr.set_voxel(led_on, off + i, off, offwi);
		fr.set_voxel(led_on, off + i, offwi, off);
		fr.set_voxel(led_on, off + i, offwi, offwi);
	}
}

//randomly set voxels
void random(Cubeframe &fr)
{
	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		for (uint8_t w = 0; w < CUBELVL_SIZE; w++)
			fr.levels[y][w] = rand();
	}
}

//randomly change voxels
void random_modify(Cubeframe &fr, Cubeframe &ref, size_t count)
{
	VoxelList vl;

	if(count > CUBE_VOLUME)
		count = CUBE_VOLUME - 1;

	uint32_t p;
	uint8_t x, y, z;

	while(count)
	{
		p = vl.pop_random_voxel();
		x = (p >> 16) & 255;
		y = (p >> 8) & 255;
		z = p & 255;

		fr.set_voxel(!ref.get_voxel(x, y ,z), x, y, z);
		count--;
	}
}

//====================
//multi-frame patterns
//====================

//make the border expand and contract
void border_bounce(size_t count, uint16_t delay)
{
	Cubeframe fr(delay);

	uint8_t start = !(CUBE_WIDTH & 1) + 1;
	uint8_t end = CUBE_WIDTH;

	fr.set(0);
	pattern::border(fr, 1, start);
	fr.draw_frame();
	start += 2;

	while(count--)
	{
		for (uint8_t w = start; w < CUBE_WIDTH; w += 2)
		{
		#ifdef PATTERN_KILLFLAG
			if(g_patternKillFlag)
				return;
		#endif

			fr.set(0);
			pattern::border(fr, 1, w);
			fr.draw_frame();
		}

		for (uint8_t w = end; ; w -= 2)
		{
		#ifdef PATTERN_KILLFLAG
			if(g_patternKillFlag)
				return;
		#endif

			fr.set(0);
			pattern::border(fr, 1, w);
			fr.draw_frame();

			if(w <= 2)
				break;
		}
	}

	fr.set(0);
	fr.draw_frame();
}

//spins a random pattern along the perimeter of the cube
void border_spin(uint8_t clockwise, cubeperim voxelperlevel, size_t count, uint16_t delay)
{
	Cubeframe fr(delay);
	fr.set(0);

	if(voxelperlevel > CUBE_WIDTH * 4 - 4)
		voxelperlevel = CUBE_WIDTH * 4 - 4 - 1;

	cubeperim collst[CUBE_WIDTH * 4 - 4];

	//build list of columns on perimeter

	if(clockwise)
	{
		cubeperim p = 0;
		for (uint8_t w = 0; w < CUBE_WIDTH; w++)
			collst[p++] = w;
		for (uint8_t w = 1; w < CUBE_WIDTH - 1; w++)
			collst[p++] = (w + 1) * CUBE_WIDTH - 1;
		for (uint8_t w = CUBE_WIDTH - 1; w; w--)
			collst[p++] = w + CUBE_WIDTH * (CUBE_WIDTH - 1);
		for (uint8_t w = CUBE_WIDTH - 1; w; w--)
			collst[p++] = w * CUBE_WIDTH;
	}else
	{
		cubeperim p = 0;
		for (uint8_t w = 0; w < CUBE_WIDTH; w++)
			collst[p++] = w * CUBE_WIDTH;
		for (uint8_t w = 1; w < CUBE_WIDTH - 1; w++)
			collst[p++] = w + CUBE_WIDTH * (CUBE_WIDTH - 1);
		for (uint8_t w = CUBE_WIDTH - 1; w; w--)
			collst[p++] = (w + 1) * CUBE_WIDTH - 1;
		for (uint8_t w = CUBE_WIDTH - 1; w; w--)
			collst[p++] = w;
	}

	cubeperim perlst[CUBE_WIDTH * 4 - 4];
	cubeperim tmpsz;
	cubeperim tmplst[CUBE_WIDTH * 4 - 4];

	for (cubeperim p = 0; p < CUBE_WIDTH * 4 - 4; p++)
		perlst[p] = p;

	uint8_t ridx;

	for (uint8_t y = 0; y < CUBE_WIDTH; y++)
	{
		memcpy(tmplst, perlst, CUBE_WIDTH * 4 - 4);
		tmpsz = CUBE_WIDTH * 4 - 4;

		for (cubeperim vpl = voxelperlevel; vpl; vpl--)
		{
			ridx = rand() % tmpsz;
			fr.set_col(fr.levels[y], 1, collst[tmplst[ridx]]);

			tmplst[ridx] = tmplst[--tmpsz];
		}
	}

	fr.draw_frame();
	count--;

	while(count--)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		//cycle voxels on perimeter
		for (uint8_t y = 0; y < CUBE_WIDTH; y++)
		{
			uint8_t g = fr.get_col(fr.levels[y], collst[0]);
			for (cubeperim c = 0; c < CUBE_WIDTH * 4 - 4 - 1; c++)
				fr.set_col(fr.levels[y], fr.get_col(fr.levels[y], collst[c + 1]), collst[c]);
			fr.set_col(fr.levels[y], g, collst[CUBE_WIDTH * 4 - 4 - 1]);
		}

		fr.draw_frame();
	}
}

//launch fireworks
void firework(uint16_t launchdelay, uint16_t explosiondelay)
{
	Cubeframe fr(launchdelay);
	fr.set(0);

	uint8_t launchx = rand() % (CUBE_WIDTH - 2) + 1;
	uint8_t launchz = rand() % (CUBE_WIDTH - 2) + 1;

	//launh the rocket

	for (uint8_t y = CUBE_WIDTH - 1; ; y--)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		if(y != CUBE_WIDTH - 1)
			fr.set_voxel(0, launchx, y + 1, launchz);
		fr.set_voxel(1, launchx, y, launchz);

		fr.draw_frame();

		if(y == 1)
			break;
	}

	fr.set_voxel(0, launchx, 0, launchz);

	uint8_t x, y, z;
	uint8_t retry = 0;

	//make explosion

	for (cubevol pieces = (CUBE_AREA * (CUBE_WIDTH - 2)) >> 2; pieces; pieces--)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		retry = 0;

		//tries to find unused random voxel, stops after 256 tries

		do {
			x = rand() % CUBE_WIDTH;
			y = rand() % (CUBE_WIDTH - 3);
			z = rand() % CUBE_WIDTH;

			retry++;
			if(!retry)
				break;
		} while(fr.get_voxel(x, y, z));

		fr.set_voxel(1, x, y, z);
	}

	fr.delayms = explosiondelay << 1;
	fr.draw_frame();
	fr.delayms >>= 1;

	//let everything fall

	for (y = 0; y < CUBE_WIDTH; y++)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		fr.set_level(0, CUBE_WIDTH - 1);
		fr.shift_plane(AXISDIR(AXIS_Y, DIR_FORWARD));
		fr.draw_frame();
	}
}

//bounce planes between edges
void plane_bounce(size_t count, uint16_t delay)
{
	Cubeframe fr(delay);
	fr.set(0);

	void (Cubeframe::*cmplane[3])(uint8_t, uint8_t) = {&Cubeframe::xplane, &Cubeframe::yplane, &Cubeframe::zplane};

	uint8_t ad = 0;
	uint8_t lastad = -1;

	while(count--)
	{
		do {
			ad = AXISDIR(rand(), rand());
		} while(ad == lastad);
		lastad = ad;

		void (Cubeframe::*planefnc)(uint8_t, uint8_t) = cmplane[GETAXIS(ad) % 3];

		for (uint8_t s = 0; s < CUBE_WIDTH; s++)
		{
		#ifdef PATTERN_KILLFLAG
			if(g_patternKillFlag)
				return;
		#endif

			if(s != 0)
				(fr.*planefnc)(0, GETDIR(ad) ? s - 1 : CUBE_WIDTH - s);
			(fr.*planefnc)(1, GETDIR(ad) ? s : CUBE_WIDTH - s - 1);
			fr.draw_frame();
		}

		fr.set(0);
	}

	fr.draw_frame();
}

//rain drops
void rain(size_t count, uint16_t delay)
{
	Cubeframe fr(delay);
	fr.set(0);

	cubecol randmin = CUBE_AREA / 8;
	cubecol randmax = CUBE_AREA / 4;

	uint8_t wait = 0;

	if(!randmin)
		randmin = 1;

	while(1)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		fr.shift_plane(AXISDIR(AXIS_Y, DIR_FORWARD));
		fr.set_level(0, 0);

		if(count)
		{
			//new droplets
			cubecol randcount = rand() % (randmax - randmin + 1) + randmin;

			if(randcount > count)
			{
				randcount = count / 2;
				if(!randcount)
					randcount = 1;
			}

			for (cubecol r = 0; r < randcount; r++)
			{
				uint8_t retry = 0;

				while(1)
				{
					cubecol col = rand() % CUBE_AREA;

					if(fr.get_col(fr.levels[0], col))
					{
						//tries to find unused random voxel, stops after 256 tries

						retry++;
						if(retry)
							continue;
					}else
					{
						fr.set_col(fr.levels[0], 1, col);
						count--;
					}

					break;
				}
			}
		}else
		{
			if(wait == CUBE_WIDTH)
				break;
			wait++;
		}

		fr.draw_frame();
	}
}

//randomly turn on/off all voxels until all are on/off
void random_set(uint8_t led_on, uint16_t delay)
{
	Cubeframe fr(delay);
	fr.set(!led_on);

	VoxelList vl;

	uint32_t p;
	uint8_t x, y, z;

	while(!vl.isempty())
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		p = vl.pop_random_voxel();
		x = (p >> 16) & 255;
		y = (p >> 8) & 255;
		z = p & 255;

		fr.set_voxel(led_on, x, y, z);
		fr.draw_frame();
	}
}

//pass voxels back and forth between edges
void send_voxel(uint8_t axis, size_t count, uint16_t delay, uint16_t leveldelay)
{
	Cubeframe fr(delay);
	fr.set(0);

	cubecol positions[CUBE_AREA];
	cubecol sides[2][(CUBE_AREA >> 1) + 1]; // +1 for odd CUBE_AREA and voxel sending
	cubecol pcount = CUBE_AREA;
	cubecol scount[2] = {0, 0};

	for (cubecol i = 0; i < CUBE_AREA; i++)
		positions[i] = i;

	cubecol idx;

	//split positions list in half randomly
	while(pcount)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		idx = rand() % pcount;
		sides[0][scount[0]++] = positions[idx];
		positions[idx] = positions[--pcount];

		if(pcount)
		{
			idx = rand() % pcount;
			sides[1][scount[1]++] = positions[idx];
			positions[idx] = positions[--pcount];
		}
	}

	//build sides
	if(axis == AXIS_X)
	{
		for (cubecol i = 0; i < scount[0]; i++)
			fr.set_voxel(1, sides[0][i] % CUBE_WIDTH, sides[0][i] / CUBE_WIDTH, 0);
		for (cubecol i = 0; i < scount[1]; i++)
			fr.set_voxel(1, sides[1][i] % CUBE_WIDTH, sides[1][i] / CUBE_WIDTH, CUBE_WIDTH - 1);
	}else
	if(axis == AXIS_Y)
	{
		for (cubecol i = 0; i < scount[0]; i++)
			fr.set_voxel(1, sides[0][i] % CUBE_WIDTH, 0, sides[0][i] / CUBE_WIDTH);
		for (cubecol i = 0; i < scount[1]; i++)
			fr.set_voxel(1, sides[1][i] % CUBE_WIDTH, CUBE_WIDTH - 1, sides[1][i] / CUBE_WIDTH);
	}else
	if(axis == AXIS_Z)
	{
		for (cubecol i = 0; i < scount[0]; i++)
			fr.set_voxel(1, 0, sides[0][i] / CUBE_WIDTH, sides[0][i] % CUBE_WIDTH);
		for (cubecol i = 0; i < scount[1]; i++)
			fr.set_voxel(1, CUBE_WIDTH - 1, sides[1][i] / CUBE_WIDTH, sides[1][i] % CUBE_WIDTH);
	}
	fr.draw_frame();

	cubecol col;
	uint8_t sd = 0;
	uint8_t ch0, ch1;

	while(count--)
	{
		//pick a random column to send over
		//always start with side 0 because it's already full when CUBE_AREA is odd

		idx = rand() % scount[sd];
		col = sides[sd][idx];

		fr.delayms = leveldelay;
		for (uint8_t i = 1; i < CUBE_WIDTH; i++)
		{
		#ifdef PATTERN_KILLFLAG
			if(g_patternKillFlag)
				return;
		#endif

			if(sd)
			{
				ch0 = CUBE_WIDTH - i;
				ch1 = CUBE_WIDTH - i - 1;
			}else
			{
				ch0 = i - 1;
				ch1 = i;
			}

			if(axis == AXIS_X)
			{
				fr.set_voxel(0, col % CUBE_WIDTH, col / CUBE_WIDTH, ch0);
				fr.set_voxel(1, col % CUBE_WIDTH, col / CUBE_WIDTH, ch1);
			}else
			if(axis == AXIS_Y)
			{
				fr.set_voxel(0, col % CUBE_WIDTH, ch0, col / CUBE_WIDTH);
				fr.set_voxel(1, col % CUBE_WIDTH, ch1, col / CUBE_WIDTH);
			}else
			if(axis == AXIS_Z)
			{
				fr.set_voxel(0, ch0, col / CUBE_WIDTH, col % CUBE_WIDTH);
				fr.set_voxel(1, ch1, col / CUBE_WIDTH, col % CUBE_WIDTH);
			}

			if(i != CUBE_WIDTH - 1)
				fr.draw_frame();
		}

		//swap column between sides
		if(sd)
		{
			sides[0][scount[0]++] = sides[1][idx];
			sides[1][idx] = sides[1][--scount[1]];
		}else
		{
			sides[1][scount[1]++] = sides[0][idx];
			sides[0][idx] = sides[0][--scount[0]];
		}

		sd ^= 1;

		fr.delayms = delay;
		fr.draw_frame();
	}
}

//sends a stream of voxels down through the cube
void stream(uint8_t axdir, size_t count, size_t spacing, uint16_t delay)
{
	Cubeframe fr(delay);

	cubevol pos = 0;
	cubevol curcount = 0, lastcount = 0;
	cubevol curspacing = 0;
	count--;

	while(1)
	{
	#ifdef PATTERN_KILLFLAG
		if(g_patternKillFlag)
			return;
	#endif

		fr.set(0);
		curcount = 0;

		for (cubevol p = pos; ; p -= spacing)
		{
			if(lastcount && curcount++ == lastcount)
				break;

			uint8_t page = p / CUBE_AREA;
			uint8_t row = p / CUBE_WIDTH % CUBE_WIDTH;
			uint8_t stream = p % CUBE_WIDTH;

			if(GETDIR(axdir) == DIR_BACKWARD)
			{
				page = CUBE_WIDTH - page - 1;
				row = CUBE_WIDTH - row - 1;
				stream = CUBE_WIDTH - stream - 1;
			}

			switch(GETAXIS(axdir))
			{
				case AXIS_X:
					fr.set_voxel(1, page, row, stream);
					break;
				case AXIS_Y:
					fr.set_voxel(1, stream, page, row);
					break;
				case AXIS_Z:
					fr.set_voxel(1, stream, row, page);
					break;
				default:
					break;
			}

			if(p < spacing)
				break;
		}

		pos++;
		if(count)
		{
			curspacing++;
			if(curspacing == spacing)
			{
				count--;
				curspacing = 0;
			}
		}else
		{
			if(!lastcount)
				lastcount = pos / spacing + 1;
		}

		//remove from list when at last voxel
		if(pos == CUBE_VOLUME)
		{
			if(lastcount)
				lastcount--;
			pos -= spacing;
		}

		fr.draw_frame();

		if(!count && !lastcount && curcount)
			break;
	}

	if(GETDIR(axdir) == DIR_BACKWARD)
	{
		fr.set_voxel(0, 0, 0, 0);
	}else
	{
		fr.set_voxel(0, CUBE_WIDTH - 1, CUBE_WIDTH - 1, CUBE_WIDTH - 1);
	}

	fr.draw_frame();
}

} //namespace pattern

} //namespace ledcube
