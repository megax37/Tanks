#include "Tank.h"

Tank::Tank(SceneNode * base, SceneNode * turret, SceneNode * antenna, BulletManager* ammo, int player) :
	Collider(-0.9f, 0.9f, 0.0f, 1.9f, -1.1f, 1.1f)
{
	tankBase = base;
	tankTurret = turret;
	tankAntenna = antenna;
	ammoManager = ammo;

	playerNumber = player;
	life = 3;

	if (playerNumber == 1)
		_position = Vector3D(0.0f, 0.0f, -5.0f);
	
	if (playerNumber == 2) {
		_position = Vector3D(0.0f, 0.0f, 5.0f);
		tankAngle = 180.0f;
	}

	_lastposition = _position;

	leftTrailRelativePos = Vector3D(0.6f, 0.2f, -1.0f);
	rightTrailRelativePos = Vector3D(-0.6f, 0.2f, -1.0f);

	bool charging = false;
	maxCharge = 500;
	minForce = 140;
	maxForce = 300;

	timeBuffer = 0;
	timeBuffer2 = 0;
}

Tank::~Tank()
{
}

void Tank::update(int elapsedTime)
{
	timeBuffer += elapsedTime;
	timeBuffer2 += elapsedTime;

	_lastposition = _position;

	float astep = 0.15f * elapsedTime;
	float vstep = 0.008f * elapsedTime;
	
	if (playerNumber == 1) {
		if (KeyBuffer::instance()->isKeyDown('a')) tankAngle += astep;
		if (KeyBuffer::instance()->isKeyDown('d')) tankAngle -= astep;
		if (KeyBuffer::instance()->isKeyDown('w')) {_position = _position + front * vstep;  }
		if (KeyBuffer::instance()->isKeyDown('s')) {_position = _position - front * vstep; }
		if (KeyBuffer::instance()->isKeyDown('z')) turretAngle += astep;
		if (KeyBuffer::instance()->isKeyDown('x')) turretAngle -= astep;

		if (charging) {
			if (!KeyBuffer::instance()->isKeyDown('q') || timeBuffer > maxCharge) charging = false, ammoManager->shoot(_position, this->getTurretFront(), this->getAngle(), this->computeForce(timeBuffer));
		}
		else {
			if (KeyBuffer::instance()->isKeyDown('q')) this->startCharging();
		}
	}
	if (playerNumber == 2) {
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_LEFT)) tankAngle += astep;
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_RIGHT)) tankAngle -= astep;
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_UP)) {_position = _position + front * vstep; }
		if (KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN)) {_position = _position - front * vstep; }
		if (KeyBuffer::instance()->isKeyDown('0')) turretAngle += astep;
		if (KeyBuffer::instance()->isKeyDown('.')) turretAngle -= astep;

		if (charging) {
			if (!KeyBuffer::instance()->isKeyDown('2') || timeBuffer > maxCharge) charging = false, ammoManager->shoot(_position, this->getTurretFront(), this->getAngle(), this->computeForce(timeBuffer));
		}
		else {
			if (KeyBuffer::instance()->isKeyDown('2')) this->startCharging();
		}
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
	tankAntenna->setMatrix(rotation(turretAngle, AXIS3D_Y));

	if ((_position - _lastposition).magnitude() > 0.1f && timeBuffer2 > 200) {
		Vector4D lpos = leftTrailRelativePos.toVec4() * (translation(_lastposition) * rotation(tankAngle, AXIS3D_Y));
		leftTrail->initParticles(lpos.toVec3());
		Vector4D rpos = rightTrailRelativePos.toVec4() * (translation(_lastposition) * rotation(tankAngle, AXIS3D_Y));
		rightTrail->initParticles(rpos.toVec3());
		timeBuffer2 = 0;
	}
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

int Tank::getLife() {
	return life;
}

bool Tank::isCharging()
{
	return charging;
}

void Tank::startCharging()
{
	charging = true;
	timeBuffer = 0;
}

int Tank::computeForce(int chargeTime)
{
	int charge = chargeTime;
	if (charge > maxCharge) charge = maxCharge;

	int force = minForce + (maxForce - minForce) * (charge / maxCharge);
	return force;
}

void Tank::setTrails(ParticleSystem * left, ParticleSystem * right)
{
	leftTrail = left;
	rightTrail = right;
}

void Tank::hitTank() {
	_position = _lastposition;
}

void Tank::hitBullet() {
	life--;
}

void Tank::reset() {
	life = 3;

	if (playerNumber == 1)
		tankAngle = 0.0f;

	if (playerNumber == 2)
		tankAngle = 180.0f;

	turretAngle = 0.0f;

	if (playerNumber == 1)
		_position = Vector3D(0.0f, 0.0f, -5.0f);

	if (playerNumber == 2)
		_position = Vector3D(0.0f, 0.0f, 5.0f);

	_lastposition = _position;
}