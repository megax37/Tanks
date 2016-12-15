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
};

#endif