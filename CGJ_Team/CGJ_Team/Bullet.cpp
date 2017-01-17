#include "Bullet.h"

Bullet::Bullet(SceneNode * bulletSceneNode) : Collider(-0.1f, 0.1f, 0.0f, 0.28f, 0.0f, 0.52f)
{
	bullet = bulletSceneNode;
	fired = false;
	vspeed = 0.01f;
	gspeed = 0.00075f;
}

Bullet::~Bullet()
{
}

void Bullet::update(int elapsedTime)
{
	float gravity = gspeed * elapsedTime;
	float vstep = vspeed * elapsedTime;

	_position = _position + velocity * vstep;
	velocity.y -= gravity;

	if (_position.y <= 0.0f) this->explode();
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

void Bullet::setForce(int force)
{
	vspeed = 0.0001f * force;
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

void Bullet::explode() {
	bullet->setVisible(false);
	this->disable();
	ParticleSystem* p = ParticleSystemManager::instance()->get("Explosion");
	if (p != nullptr) p->initParticles(_position);
	else std::cout << "Nao explodiu, demasiadas explosoes..." << std::endl;
}

void Bullet::reset() {
	bullet->setVisible(false);
	this->disable();
}
