#include "Entity.h"

Entity* Entity::entities[256];

Entity::Entity(unsigned int id, int texture) : id(id),
		textureFaces{texture,texture,texture,texture,texture,texture,texture,texture,texture,texture,texture,texture},
		emission{0,0,0}{
}
