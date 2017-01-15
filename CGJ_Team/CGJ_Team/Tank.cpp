#include "Tank.h"

Tank::Tank(SceneNode * base, SceneNode * FLwheel, SceneNode * FRwheel, SceneNode * BLwheel, SceneNode * BRwheel, SceneNode * turret, int player) :
	Collider(-0.9f, 0.9f, 0.0f, 1.9f, -1.1f, 1.1f)
{
	tankBase = base;
	frontLeftWheel = FLwheel;
	frontRightWheel = FRwheel;
	backLeftWheel = BLwheel;
	backRightWheel = BRwheel;
	tankTurret = turret;

	playerNumber = player;

	if (playerNumber == 1)
		_position = Vector3D(0.0f, 0.0f, -5.0f);
	
	if (playerNumber == 2)
		_position = Vector3D(0.0f, 0.0f, 5.0f);
	_lastposition = _position;
}

Tank::~Tank()
{
}

void Tank::update(int elapsedTime)
{
	float astep = 0.15f * elapsedTime;
	float vstep = 0.008f * elapsedTime;

	
	if (playerNumber == 1) {
		if (KeyBuffer::instance()->isKeyDown('a')) tankAngle += astep;
		if (KeyBuffer::instance()->isKeyDown('d')) tankAngle -= astep;
		if (KeyBuffer::instance()->isKeyDown('w')) { _lastposition = _position; _position = _position + front * vstep;  }
		if (KeyBuffer::instance()->isKeyDown('s')) { _lastposition = _position; _position = _position - front * vstep; }
		if (KeyBuffer::instance()->isKeyDown('z')) turretAngle += astep;
		if (KeyBuffer::instance()->isKeyDown('x')) turretAngle -= astep;
	}
	if (playerNumber == 2) {
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_LEFT)) tankAngle += astep;
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_RIGHT)) tankAngle -= astep;
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_UP)) { _lastposition = _position; _position = _position + front * vstep; }
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN)) { _lastposition = _position; _position = _position - front * vstep; }
		if (KeyBuffer::instance()->isKeyDown('0')) turretAngle += astep;
		if (KeyBuffer::instance()->isKeyDown('.')) turretAngle -= astep;
	}

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
	tankBase->setMatrix(translation(_position) * rotation(tankAngle, AXIS3D_Y));
	tankTurret->setMatrix(rotation(turretAngle, AXIS3D_Y));
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

void Tank::hitTank() {
	_position = _lastposition;
}

void Tank::hitBullet() {
	std::cout << "drop life " + playerNumber << std::endl;
}