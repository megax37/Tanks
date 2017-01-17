#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "SceneNode.h"
#include "Collider.h"
#include "ParticleSystemManager.h"

class Bullet : public Collider
{
public:
	Bullet(SceneNode * bulletSceneNode);
	~Bullet();

	void update(int elapsedTime);
	void move();

	void setVelocity(Vector3D vel);
	void setAngle(float theta);
	void setForce(int force);

	void enable();
	void disable();
	bool isFired();
	void explode();
	void reset();

private:

	SceneNode* bullet;

	float vspeed;
	float gspeed;

	Vector3D velocity;
	float angle = 0; 
	
	bool fired;

	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
};

#endif