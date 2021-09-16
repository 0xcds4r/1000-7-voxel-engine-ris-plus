#ifndef VOXELS_WORLDGENERATOR_H_
#define VOXELS_WORLDGENERATOR_H_

#include "Chunk.h"
#include "Chunks.h"

class voxel;

class WorldGenerator {
public:
	static void generate(Chunks* chunks, voxel* voxels, int x, int y, int z);
};

#endif /* VOXELS_WORLDGENERATOR_H_ */
