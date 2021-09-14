#include "Block.h"
#include "Blocks.h"

void Blocks::initialize()
{
	// AIR
	Block* block = new Block(0,0);
	block->drawGroup = 1;
	block->lightPassing = true;
	block->obstacle = false;
	Block::blocks[block->id] = block;

	// STONE
	block = new Block(1,2);
	Block::blocks[block->id] = block;

	// GRASS
	block = new Block(2,4);
	block->textureFaces[2] = 2;
	block->textureFaces[3] = 1;
	Block::blocks[block->id] = block;

	// LAMP
	block = new Block(3,3);
	block->emission[0] = 15;
	block->emission[1] = 14;
	block->emission[2] = 13;
	Block::blocks[block->id] = block;

	// GLASS
	block = new Block(4,5);
	block->drawGroup = 2;
	block->lightPassing = true;
	Block::blocks[block->id] = block;

	// PLANKS
	block = new Block(5,6);
	Block::blocks[block->id] = block;
}