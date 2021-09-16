#ifndef VOXELS_ENTITY_H_
#define VOXELS_ENTITY_H_

class Entity {
public:
	static Entity* entities[256];

	const unsigned int id;
						
	int textureFaces[12]; 
	unsigned char emission[3];
	unsigned char drawGroup = 0;
	bool lightPassing = false;
	bool obstacle = true;

	Entity(unsigned int id, int texture);
};

#endif /* VOXELS_ENTITY_H_ */
