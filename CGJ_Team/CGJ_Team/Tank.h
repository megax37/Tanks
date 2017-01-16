#ifndef _TANK_
#define _TANK_

#include "SceneNode.h"
#include "Collider.h"

class Tank : public Collider
{
public:
	Tank(SceneNode* tankBase, SceneNode* frontLeftWheel, SceneNode* frontRightWheel, SceneNode* backLeftWheel, SceneNode* backRightWheel, SceneNode* tankTurret, int player);
	~Tank();

	void update(int elapsedTime);
	void move();
	void hitTank();
	void hitBullet();

	Vector3D getFront();
	Vector3D getTurretFront();
	float getAngle();
	int getLife();

	
private:

	SceneNode* tankBase, *frontLeftWheel, *frontRightWheel, *backLeftWheel, *backRightWheel, *tankTurret;

	int playerNumber = 1;
	int life = 3;

	float vspeed = 0.0025f;
	float aspeed = 0.05f;

	Vector3D front, turretFront;

	float tankAngle = 0.0f;
	float turretAngle = 0.0f;

	Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);
};

#endif