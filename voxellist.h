#ifndef __VOXELLIST_H
#define __VOXELLIST_H

#include "cubemap.h"

#ifndef VL_LINEAR
	#if CUBE_WIDTH <= 6
		//this uses less memory when CUBE_WIDTH < 6
		#define VL_LINEAR 1
	#else
		#define VL_LINEAR 0
	#endif
#endif

namespace ledcube
{
	//designed to be fastest with minimal memory footprint on pop_random

	class VoxelList
	{
	private:
	#if VL_LINEAR
		cubevol voxels[CUBE_WIDTH * CUBE_AREA];
		uint16_t voxelcount;
	#else
		cubecol cols[CUBE_WIDTH][CUBE_AREA];
		cubecol colsz[CUBE_WIDTH];
		uint8_t levels[CUBE_WIDTH];
		uint8_t levelsz;
	#endif

	public:
		VoxelList();
		void randomize();
		uint32_t pop_random_voxel();
		int isempty();
	};
}
#endif //ndef __VOXELLIST_H
