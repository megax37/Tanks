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
	if (KeyBuffer::instance()->isKeyDown('z')) turretAngle += astep;
	if (KeyBuffer::instance()->isKeyDown('x')) turretAngle -= astep;

	Quaternion qr(tankAngle, AXIS3D_Y);
	Quaternion qi(AXIS3D_Z);
	Quaternion qf = qr * qi * qInverse(qr);
	front = Vector3D(qf.x, qf.y, qf.z);
	Quaternion turretQR(turretAngle + tankAngle, AXIS3D_Y);
	Quaternion turretQI(AXIS3D_Z);
	Quaternion turretQ = turretQR * turretQI * qInverse(turretQR);
	turretFront = Vector3D(turretQ.x, turretQ.y, turretQ.z);
}

void Tank::move()
{
	tankBase->setMatrix(translation(position) * rotation(tankAngle, AXIS3D_Y));
	tankTurret->setRotation(rotation(turretAngle, AXIS3D_Y));
}

Vector3D Tank::getPosition() {
	return position;
}
Vector3D Tank::getFront() {
	return front;
}

Vector3D Tank::getTurretFront() {
	return turretFront;
}

float Tank::getAngle() {
	return turretAngle + tankAngle;
}