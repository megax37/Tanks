#include "BulletManager.h"

BulletManager::BulletManager(SceneNode * baseNode) {
	baseSceneNode = baseNode;
}
BulletManager::~BulletManager() {
	/*for each (Bullet * bullet in bullets)
	{
		destroy bullet;
	}*/
}

void BulletManager::update(int elapsedTime) {
	for each (Bullet * bullet in bullets)
	{
		bullet->update(elapsedTime);
	}
}

void BulletManager::shoot(Vector3D initialPosition, Vector3D front, float angle) {
	Mesh* mesh;
	Material* mat;

	ShaderProgram* shader = ShaderProgramManager::instance()->get("tank");
	mesh = MeshManager::instance()->get("Bullet");
	mat = MaterialManager::instance()->get("Bullet");
	SceneNode * bulletSceneNode = baseSceneNode->createNode();
	bulletSceneNode->setMesh(mesh);
	bulletSceneNode->setMaterial(mat);
	bulletSceneNode->setShaderProgram(shader);
	Bullet * var = new Bullet(bulletSceneNode, initialPosition, front, angle);
	bullets.push_back(var);
}

void BulletManager::move() {
	for each (Bullet * bullet in bullets)
	{
		bullet->move();
	}
}
