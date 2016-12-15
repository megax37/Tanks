#include "BulletManager.h"

BulletManager::BulletManager(SceneNode * baseNode) {
	baseSceneNode = baseNode;
	shooting = false;
	timeBuffer = 0;
}
BulletManager::~BulletManager() {
	/*for each (Bullet * bullet in bullets)
	{
		destroy bullet;
	}*/
}

void BulletManager::update(int elapsedTime) {
	if (shooting && timeBuffer > 1000) {
		addBullet();
		shooting = false;
		timeBuffer = 0;
	}
	else shooting = false;
	for each (Bullet * bullet in bullets)
	{
		bullet->update(elapsedTime);
	}
	timeBuffer += elapsedTime;
}

void BulletManager::shoot(Vector3D initialPosition, Vector3D front, float angle) {
	shooting = true;
	lastAngle = angle;
	lastFront = front;
	lastPosition = initialPosition;
}

void BulletManager::addBullet() {
	Mesh* mesh;
	Material* mat;

	ShaderProgram* shader = ShaderProgramManager::instance()->get("tank");
	mesh = MeshManager::instance()->get("Bullet");
	mat = MaterialManager::instance()->get("Bullet");
	SceneNode * bulletSceneNode = baseSceneNode->createNode();
	bulletSceneNode->setMesh(mesh);
	bulletSceneNode->setMaterial(mat);
	bulletSceneNode->setShaderProgram(shader);
	Bullet * var = new Bullet(bulletSceneNode, lastPosition + offsetPosition, lastFront, lastAngle);
	bullets.push_back(var);
}

void BulletManager::move() {
	for each (Bullet * bullet in bullets)
	{
		bullet->move();
	}
}
