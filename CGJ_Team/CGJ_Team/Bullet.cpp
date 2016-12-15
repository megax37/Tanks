#include "Bullet.h"

Bullet::Bullet(SceneNode * bulletSceneNode, Vector3D initialPosition, Vector3D frontVector, float tankAngle)
{
	bullet = bulletSceneNode;
	position = initialPosition;
	front = frontVector;
	angle = tankAngle;

	timeToDestroy = 5000.0f;
	destroy = false;
}

Bullet::~Bullet()
{
	delete bullet;
}

void Bullet::update(int elapsedTime)
{
	float astep = 0.15f * elapsedTime;
	float vstep = 0.008f * elapsedTime;

	position = position + front * vstep;

	timeToDestroy -= elapsedTime;
}

bool Bullet::isToDestroy()
{
	return timeToDestroy < 0.0f;
}

void Bullet::move()
{
	bullet->setMatrix(translation(position) * rotation(angle, AXIS3D_Y));
}



