#include "voxellist.h"
#include <stdlib.h>
#include <string.h>

namespace ledcube {

VoxelList::VoxelList()
{
#if VL_LINEAR
	for (cubevol v = 0; v < CUBE_WIDTH * CUBE_AREA; v++)
		this->voxels[v] = v;
	this->voxelcount = CUBE_WIDTH * CUBE_AREA;
#else
	this->levelsz = CUBE_WIDTH;

	for (cubecol i = 0; i < CUBE_AREA; i++)
		this->cols[0][i] = i;
	this->levels[0] = 0;
	this->colsz[0] = CUBE_AREA;

	for (uint8_t y = 1; y < CUBE_WIDTH; y++)
	{
		memcpy(this->cols[y], this->cols[0], sizeof(this->cols[0]));
		this->levels[y] = y;
		this->colsz[y] = CUBE_AREA;
	}
#endif
}

void VoxelList::randomize()
{
#if VL_LINEAR
	//perform in-place shuffle to save memory
	// https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/

	for (cubevol i = CUBE_WIDTH * CUBE_AREA - 1; i > 0; i--)
	{
		cubevol j = rand() % (i + 1);

		cubevol tmp = this->voxels[i];
		this->voxels[i] = this->voxels[j];
		this->voxels[j] = tmp;
	}
#else
	#warning Not implemented for CUBE_WIDTH >= 16
#endif
}

//pops a random voxel from the list of all voxels, non-replacement
//returns (x << 16) | (y << 8) | z
uint32_t VoxelList::pop_random_voxel()
{
#if VL_LINEAR
	static bool calledRandom = false;
	if(!calledRandom)
	{
		this->randomize();
		calledRandom = true;
	}

	if(this->isempty())
		return -1;

	return Cubeframe::vox_to_xyz(this->voxels[--this->voxelcount]);
#else
	if(this->isempty())
		return -1;

	uint8_t yidx = rand() % this->levelsz;
	cubecol cidx = rand() % this->colsz[yidx];

	cubecol col = this->cols[yidx][cidx];
	uint32_t r = ((col % CUBE_WIDTH) << 16) | (this->levels[yidx] << 8) | (col / CUBE_WIDTH);

	this->cols[yidx][cidx] = this->cols[yidx][--this->colsz[yidx]];

	if(!this->colsz[yidx])
	{
		this->levelsz--;
		if(yidx != this->levelsz)
		{
			this->levels[yidx] = this->levels[this->levelsz];
			this->colsz[yidx] = this->colsz[this->levelsz];
			memcpy(this->cols[yidx], this->cols[this->levelsz], this->colsz[yidx] * sizeof(cubecol));
		}
	}

	return r;
#endif
}

int VoxelList::isempty()
{
#if VL_LINEAR
	return !this->voxelcount;
#else
	return !this->levelsz;
#endif
}

} //namespace ledcube
