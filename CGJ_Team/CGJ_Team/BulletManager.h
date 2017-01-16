#pragma once
#ifndef _BULLETMANAGER_
#define _BULLETMANAGER_

#include "SceneNode.h"
#include "Bullet.h"
#include "ShaderProgramManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"
#include "Tank.h"

class BulletManager
{
public:

	BulletManager(SceneNode * baseNode, int bulletCount);
	~BulletManager();

	void update(int elapsedTime);
	void shoot(Vector3D initialPosition, Vector3D front, float angle);
	void move();
	void checkCollisions(Tank * tank);
	void reset();

private:

	SceneNode* baseSceneNode;
	std::vector<Bullet*> bullets;

	Vector3D offsetPosition = Vector3D(0.1f, 1.25f, 0.0f);
	Vector3D offsetVelocity = Vector3D(0.0f, 0.2f, 0.0f);

	bool shooting;
	int timeBuffer;
};

#endif