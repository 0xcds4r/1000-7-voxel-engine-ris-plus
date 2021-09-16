#include "WorldGenerator.h"
#include "voxel.h"

#include "Level.h"

#include <math.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/noise.hpp"

void WorldGenerator::generate(Chunks* chunks, voxel* voxels, int cx, int cy, int cz)
{
	int iSavedX = 0, iSavedY = 0, iSavedZ = 0;

	for (int z = 0; z < CHUNK_D; z++)
	{
		for (int x = 0; x < CHUNK_W; x++)
		{
			int real_x = x + cx * CHUNK_W;
			int real_z = z + cz * CHUNK_D;

			float height = glm::perlin(glm::vec3(real_x*0.0125f,real_z*0.0125f, 0.0f));
			height += glm::perlin(glm::vec3(real_x*0.025f,real_z*0.025f, 0.0f))*0.5f;

			height *= 0.1f;
			height += 0.05f;
			for (int y = 0; y < CHUNK_H; y++)
			{
				int real_y = y + cy * CHUNK_H;

				float noise = height;
				int id = noise / std::fmax(0.01f, real_y*0.1f + 0.1f) > 0.1f;

				if (real_y < 15) {
					id = 1;
				}

				if (real_y == 15) 
				{
					iSavedX = real_x;
					iSavedY = real_y;
					iSavedZ = real_z;
					id = 2;
				}

				voxels[(y * CHUNK_D + z) * CHUNK_W + x].id = id;
			}
		}
	}
}