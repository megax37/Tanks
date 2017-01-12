#include "BulletManager.h"

BulletManager::BulletManager(SceneNode * baseNode, int bulletCount) {
	baseSceneNode = baseNode;
	shooting = false;
	timeBuffer = 0;

	Mesh* mesh = MeshManager::instance()->get("Bullet");
	Material* mat = MaterialManager::instance()->get("Bullet");
	ShaderProgram* shader = ShaderProgramManager::instance()->get("tank");

	SceneNode * bulletSceneNode;
	Bullet * bulletObj;
	for (int i = 0; i < bulletCount; i++) {
		bulletSceneNode = baseSceneNode->createNode();
		bulletSceneNode->setMesh(mesh);
		bulletSceneNode->setMaterial(mat);
		bulletSceneNode->setShaderProgram(shader);
		bulletSceneNode->setVisible(false);

		bulletObj = new Bullet(bulletSceneNode);
		bullets.push_back(bulletObj);
	}
	
}
BulletManager::~BulletManager() {
	/*for each (Bullet * bullet in bullets)
	{
		destroy bullet;
	}*/
}

void BulletManager::update(int elapsedTime) {
	/*if (shooting && timeBuffer > 1000) {
		addBullet();
		shooting = false;
		timeBuffer = 0;
	}
	else shooting = false;*/

	/*for (int i = 0; i < bullets.size(); i++)
	{
		if(bullets[i]->isToDestroy())
		{
			Bullet * b = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete b;
			break;
		}
	}*/
	for each (Bullet * bullet in bullets)
	{
		if(bullet->isFired()) bullet->update(elapsedTime);
	}
	timeBuffer += elapsedTime;
}

void BulletManager::shoot(Vector3D initialPosition, Vector3D front, float angle) {
	/*shooting = true;
	lastAngle = angle;
	lastFront = front;
	lastPosition = initialPosition;*/

	if (timeBuffer > 300) {
		for each (Bullet * bullet in bullets)
		{
			if (!(bullet->isFired())) {
				bullet->setPosition(initialPosition + offsetPosition);
				bullet->setVelocity(front + offsetVelocity);
				bullet->setAngle(angle);
				bullet->enable();
				timeBuffer = 0;
				break;
			}
		}
	}
}

void BulletManager::addBullet() {
	/*Mesh* mesh;
	Material* mat;

	ShaderProgram* shader = ShaderProgramManager::instance()->get("tank");
	mesh = MeshManager::instance()->get("Bullet");
	mat = MaterialManager::instance()->get("Bullet");
	SceneNode * bulletSceneNode = baseSceneNode->createNode();
	bulletSceneNode->setMesh(mesh);
	bulletSceneNode->setMaterial(mat);
	bulletSceneNode->setShaderProgram(shader);
	Bullet * var = new Bullet(bulletSceneNode, lastPosition + offsetPosition, lastFront, lastAngle);
	bullets.push_back(var);*/
}

void BulletManager::move() {
	for each (Bullet * bullet in bullets)
	{
		if (bullet->isFired()) bullet->move();
	}
}
