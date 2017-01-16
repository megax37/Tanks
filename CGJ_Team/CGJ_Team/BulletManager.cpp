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

}

void BulletManager::update(int elapsedTime) {

	for each (Bullet * bullet in bullets)
	{
		if(bullet->isFired()) bullet->update(elapsedTime);
	}
	timeBuffer += elapsedTime;
}

void BulletManager::shoot(Vector3D initialPosition, Vector3D front, float angle) {

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

void BulletManager::move() {
	for each (Bullet * bullet in bullets)
	{
		if (bullet->isFired()) bullet->move();
	}
}

void BulletManager::checkCollisions(Tank * tank) {
	for each(Bullet * bullet in bullets) {
		if (bullet->isFired() && bullet->collides(tank)) {
			bullet->explode();
			tank->hitBullet();
		}
	}
}

void BulletManager::reset() {
	shooting = false;
	timeBuffer = 0;

	for each (Bullet * bullet in bullets) {
		bullet->reset();
	}
}