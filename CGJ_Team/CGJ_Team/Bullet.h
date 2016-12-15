#pragma once
#ifndef _BULLET_
#define _BULLET_

#include "SceneNode.h"
#include "Object.h"

class Bullet : Object
{
public:
	Bullet(SceneNode * bulletSceneNode, Vector3D initialPosition, Vector3D frontVector, float angle);
	~Bullet();

	void update(int elapsedTime);
	void move();
private:

	SceneNode* bullet;

	float vspeed = 0.0025f;
	float aspeed = 0.05f;

	Vector3D position, front;
	float angle = 0; 

	Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);
};

#endif