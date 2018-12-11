#include "voxellist.h"
#include <stdlib.h>
#include <string.h>

namespace ledcube {

VoxelList::VoxelList()
{
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
}

//pops a random voxel from the list of all voxels, non-replacement
//returns (x << 16) | (y << 8) | z
uint32_t VoxelList::pop_random_voxel()
{
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
}

int VoxelList::isempty()
{
	return !this->levelsz;
}

} //namespace ledcube
