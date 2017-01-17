#ifndef _STATICOBJECT_
#define _STATICOBJECT_

#include "Collider.h"

class StaticObject : public Collider
{
public:
	StaticObject(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void update(int elapsedTime);
	void move();
};

#endif