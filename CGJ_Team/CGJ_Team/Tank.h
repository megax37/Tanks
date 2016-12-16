#ifndef _TANK_
#define _TANK_

#include "SceneNode.h"
#include "Object.h"
class Tank : Object
{
public:
	Tank(SceneNode* tankBase, SceneNode* frontLeftWheel, SceneNode* frontRightWheel, SceneNode* backLeftWheel, SceneNode* backRightWheel, SceneNode* tankTurret);
	~Tank();

	void update(int elapsedTime);
	void move();
	Vector3D getPosition();
	Vector3D getFront();
	Vector3D getTurretFront();
	float getAngle();

	
private:

	SceneNode* tankBase, *frontLeftWheel, *frontRightWheel, *backLeftWheel, *backRightWheel, *tankTurret;

	float vspeed = 0.0025f;
	float aspeed = 0.05f;

	Vector3D position, front, turretFront;

	float tankAngle = 0.0f;
	float turretAngle = 0.0f;

	Vector3D AXIS3D_X = Vector3D(1.0f, 0.0f, 0.0f);
	Vector3D AXIS3D_Y = Vector3D(0.0f, 1.0f, 0.0f);
	Vector3D AXIS3D_Z = Vector3D(0.0f, 0.0f, 1.0f);
};

#endif