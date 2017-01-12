#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "SceneNode.h"
#include "Object.h"

class Bullet : Object
{
public:
	Bullet(SceneNode * bulletSceneNode);
	~Bullet();

	void update(int elapsedTime);
	bool isToDestroy();
	void move();

	void setPosition(Vector3D pos);
	void setVelocity(Vector3D vel);
	void setAngle(float theta);

	void enable();
	void disable();
	bool isFired();

private:

	SceneNode* bullet;

	float vspeed = 0.0025f;
	float aspeed = 0.05f;

	Vector3D position, velocity;
	float angle = 0; 
	
	bool fired;

	float timeToDestroy;
	bool destroy;

	Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);
};

#endif