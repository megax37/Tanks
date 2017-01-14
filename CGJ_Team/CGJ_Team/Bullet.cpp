#include "Bullet.h"

Bullet::Bullet(SceneNode * bulletSceneNode) : Collider(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)
{
	bullet = bulletSceneNode;
	fired = false;
}

Bullet::~Bullet()
{
	//delete bullet;
}

void Bullet::update(int elapsedTime)
{
	float gravity = 0.0002f * elapsedTime;
	float vstep = 0.009f * elapsedTime;

	_position = _position + velocity * vstep;
	velocity.y -= gravity;

	if (_position.y <= 0.0f) {
		bullet->setVisible(false);
		this->disable();
	}

	//timeToDestroy -= elapsedTime;
}

bool Bullet::isToDestroy()
{
	return timeToDestroy < 0.0f;
}

void Bullet::move()
{
	bullet->setMatrix(translation(_position) * rotation(angle, AXIS3D_Y));
}

void Bullet::setVelocity(Vector3D vel)
{
	velocity = vel;
}

void Bullet::setAngle(float theta)
{
	angle = theta;
}

void Bullet::enable()
{
	fired = true;
	bullet->setVisible(true);
}

void Bullet::disable()
{
	fired = false;
}

bool Bullet::isFired()
{
	return fired;
}



