#ifndef _COLLIDER_
#define _COLLIDER_

#include "Object.h"
#include "VectorFactory.h"

class Collider : public Object
{
protected:
	Vector3D _position;
	Vector3D _lastposition;
private:
	float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
	
public:
	Collider(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

	bool collides(Collider * collider);

	float getMinX();
	float getMinY();
	float getMinZ();

	float getMaxX();
	float getMaxY();
	float getMaxZ();

	Vector3D getPosition();
	void setPosition(Vector3D v);
};
#endif