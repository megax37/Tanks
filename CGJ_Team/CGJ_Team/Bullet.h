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

	void enable();
	void disable();
	bool isFired();
	void explode();

private:

	SceneNode* bullet;

	float vspeed = 0.009f;
	float gspeed = 0.0002f;

	Vector3D velocity;
	float angle = 0; 
	
	bool fired;

	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
};

#endif