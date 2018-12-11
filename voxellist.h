#ifndef __VOXELLIST_H
#define __VOXELLIST_H

#include "cubemap.h"

class VoxelList
{
private:
	cubecol cols[CUBE_WIDTH][CUBE_AREA];
	cubecol colsz[CUBE_WIDTH];
	uint8_t levels[CUBE_WIDTH];
	uint8_t levelsz;
public:
	VoxelList();
	uint32_t pop_random_voxel();
	int isempty();
};

#endif //ndef __VOXELLIST_H
