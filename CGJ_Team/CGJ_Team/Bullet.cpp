#include "Bullet.h"

Bullet::Bullet(SceneNode * bulletSceneNode, Vector3D initialPosition, Vector3D frontVector, float tankAngle)
{
	bullet = bulletSceneNode;
	position = initialPosition;
	front = frontVector;
	angle = tankAngle;
}

Bullet::~Bullet()
{
}

void Bullet::update(int elapsedTime)
{
	float astep = 0.15f * elapsedTime;
	float vstep = 0.008f * elapsedTime;

	position = position + front * vstep;
}

void Bullet::move()
{
	bullet->setMatrix(translation(position) * rotation(angle, AXIS3D_Y));
}



