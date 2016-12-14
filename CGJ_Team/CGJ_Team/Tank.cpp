#include "Tank.h"

Tank::Tank(SceneNode * base, SceneNode * FLwheel, SceneNode * FRwheel, SceneNode * BLwheel, SceneNode * BRwheel, SceneNode * turret)
{
	tankBase = base;
	frontLeftWheel = FLwheel;
	frontRightWheel = FRwheel;
	backLeftWheel = BLwheel;
	backRightWheel = BRwheel;
	tankTurret = turret;

	position = Vector3D();
}

Tank::~Tank()
{
}

void Tank::update(int elapsedTime)
{
	float astep = 0.15f * elapsedTime;
	float vstep = 0.008f * elapsedTime;

	if (KeyBuffer::instance()->isKeyDown('a')) tankAngle += astep;
	if (KeyBuffer::instance()->isKeyDown('d')) tankAngle -= astep;
	if (KeyBuffer::instance()->isKeyDown('w')) position = position + front * vstep;
	if (KeyBuffer::instance()->isKeyDown('s')) position = position - front * vstep;

	Quaternion qr(tankAngle, AXIS3D_Y);
	Quaternion qi(AXIS3D_Z);
	Quaternion qf = qr * qi * qInverse(qr);
	front = Vector3D(qf.x, qf.y, qf.z);
}

void Tank::move()
{
	tankBase->setMatrix(translation(position) * rotation(tankAngle, AXIS3D_Y));
}
