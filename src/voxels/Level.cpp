#include "Level.h"

Chunks* Level::chunks = 0;
WorldFiles* Level::wfile = 0;

void Level::initialize()
{
	Level::wfile = new WorldFiles("world/", REGION_VOL * (CHUNK_VOL * 2 + 8));
	Level::chunks = new Chunks(32,1,32, 0,0,0);
	Lighting::initialize(Level::chunks);
}

WorldFiles* Level::getData()
{
	return Level::wfile;
}

void Level::destroy()
{
	if(Level::chunks) 
	{
		delete Level::chunks;
		Level::chunks = 0;
	}

	if(Level::wfile) 
	{
		delete Level::wfile;
		Level::wfile = 0;
	}
}

void Level::setBlock(int x, int y, int z, int block)
{
	Level::getChunks()->set(x, y, z, block);
	Lighting::onBlockSet(x, y, z, block);
}

void Level::growTree(int x, int y, int z)
{
	Level::getChunks()->createTree(x, y, z);
}

Chunks* Level::getChunks()
{
	return Level::chunks;
}

// Save all world data to files
void Level::writeData()
{
	for (unsigned int i = 0; i < Level::getChunks()->volume; i++)
	{
		Chunk* chunk = Level::getChunks()->chunks[i];
		if (chunk == nullptr) {
			continue;
		}

		Level::getData()->put((const char*)chunk->voxels, chunk->x, chunk->z);
	}

	Level::getData()->write();
}

// Deleting world data from memory
void Level::closeData()
{
	Level::destroy();
}