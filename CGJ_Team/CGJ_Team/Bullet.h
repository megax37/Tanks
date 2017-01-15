#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "SceneNode.h"
#include "Collider.h"

class Bullet : public Collider
{
public:
	Bullet(SceneNode * bulletSceneNode);
	~Bullet();

	void update(int elapsedTime);
	bool isToDestroy();
	void move();

	void setVelocity(Vector3D vel);
	void setAngle(float theta);

	void enable();
	void disable();
	bool isFired();
	void explode();

private:

	SceneNode* bullet;

	float vspeed = 0.0025f;
	float aspeed = 0.05f;

	Vector3D velocity;
	float angle = 0; 
	
	bool fired;

	float timeToDestroy;
	bool destroy;

	Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);
};

#endif