#include "Collider.h"

Collider::Collider(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	_minX = minX;
	_maxX = maxX;
	_minY = minY;
	_maxY = maxY;
	_minZ = minZ;
	_maxZ = maxZ;
}

bool Collider::collides(Collider * c) {
	return (getMinX() <= c->getMaxX() && getMaxX() >= c->getMinX()) &&
		(getMinY() <= c->getMaxY() && getMaxY() >= c->getMinY()) &&
		(getMinZ() <= c->getMaxZ() && getMaxZ() >= c->getMinZ());
}


float Collider::getMinX() {
	return getPosition().x + _minX;
}
float Collider::getMinY() {
	return getPosition().y + _minY;
}
float Collider::getMinZ() {
	return getPosition().z + _minZ;
}

float Collider::getMaxX() {
	return getPosition().x + _maxX;
}
float Collider::getMaxY() {
	return getPosition().y + _maxY;
}
float Collider::getMaxZ() {
	return getPosition().z + _maxZ;
}

Vector3D Collider::getPosition()
{
	return _position;
}

void Collider::setPosition(Vector3D v)
{
	_position = v;
}