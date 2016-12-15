#pragma once
#ifndef _BULLETMANAGER_
#define _BULLETMANAGER_

#include "SceneNode.h"
#include "Bullet.h"
#include "ShaderProgramManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

class BulletManager
{
public:
	BulletManager(SceneNode * baseNode);
	~BulletManager();

	void update(int elapsedTime);
	void shoot(Vector3D initialPosition, Vector3D front, float angle);
	void move();
private:
	SceneNode* baseSceneNode;
	std::vector<Bullet*> bullets;
	Vector3D lastPosition, lastFront;
	Vector3D offsetPosition = Vector3D(0.0f, 1.4f, 0.0f);
	float lastAngle;
	bool shooting;
	int timeBuffer;

	void addBullet();
	void removeBullet();
};

#endif