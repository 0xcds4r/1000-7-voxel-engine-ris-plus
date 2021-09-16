#ifndef VOXELS_LEVEL_H_
#define VOXELS_LEVEL_H_

#include "Chunks.h"
#include "../lighting/Lighting.h"
#include "../files/WorldFiles.h"
#include "../voxels/Chunk.h"

class Level
{
public:
	static Chunks* chunks;
	static WorldFiles* wfile;

	static void initialize();
	static void destroy();
	static void setBlock(int x, int y, int z, int block);
	static Chunks* getChunks();
	static WorldFiles* getData();
	static void writeData();
	static void closeData();
	static void growTree(int x, int y, int z);
};

#endif