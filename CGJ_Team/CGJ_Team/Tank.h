#ifndef _TANK_
#define _TANK_

class BulletManager;

#include "SceneNode.h"
#include "Collider.h"
#include "ParticleSystemManager.h"
#include "BulletManager.h"

class Tank : public Collider
{
public:
	Tank(SceneNode* tankBase, SceneNode* tankTurret, BulletManager* ammo, int player);
	~Tank();

	void update(int elapsedTime);
	void move();
	void hitTank();
	void hitBullet();
	void reset();

	Vector3D getFront();
	Vector3D getTurretFront();
	float getAngle();
	int getLife();

	bool isCharging();
	void startCharging();

	void setTrails(ParticleSystem* left, ParticleSystem* right);

	
private:

	SceneNode* tankBase, *tankTurret;

	int playerNumber = 1;
	int life = 3;

	float vspeed = 0.0025f;
	float aspeed = 0.05f;

	Vector3D front, turretFront;

	float tankAngle = 0.0f;
	float turretAngle = 0.0f;

	ParticleSystem* leftTrail, *rightTrail;
	Vector3D leftTrailRelativePos;
	Vector3D rightTrailRelativePos;
	int timeBuffer, timeBuffer2;

	BulletManager* ammoManager;
	bool charging;
	int maxCharge;
	int minForce, maxForce;

	int computeForce(int chargeTime);

	Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);
};

#endif