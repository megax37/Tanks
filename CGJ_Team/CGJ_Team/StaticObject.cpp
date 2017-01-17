#include "StaticObject.h"

void StaticObject::update(int time) {

}

void StaticObject::move() {

}

StaticObject::StaticObject(Vector3D position, float minX, float maxX, float minY, float maxY, float minZ, float maxZ) : Collider(minX, maxX, minY, maxY, minZ, maxZ)
{
	_position = position;
}