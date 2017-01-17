#define _USE_MATH_DEFINES

#include "VectorFactory.h"

Vector2D::Vector2D() {
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D operator+(const Vector2D& vector1, const Vector2D& vector2) {
	float tempX = vector1.x + vector2.x;
	float tempY = vector1.y + vector2.y;
	return Vector2D::Vector2D(tempX, tempY);
}

Vector2D operator-(const Vector2D& vector1, const Vector2D& vector2) {
	float tempX = vector1.x - vector2.x;
	float tempY = vector1.y - vector2.y;
	return Vector2D::Vector2D(tempX, tempY);
}

Vector2D operator-(const Vector2D& vector) {
	return Vector2D::Vector2D(-vector.x, -vector.y);
}

Vector2D operator*(const float& scalar, const Vector2D& vector) {
	float tempX = vector.x * scalar;
	float tempY = vector.y * scalar;
	return Vector2D::Vector2D(tempX, tempY);
}

Vector2D operator*(const Vector2D& vector, const float& scalar) {
	float tempX = vector.x * scalar;
	float tempY = vector.y * scalar;
	return Vector2D::Vector2D(tempX, tempY);
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vector) {
	out << "(" << vector.x << ", " << vector.y << ")";
	return out;
}

float Vector2D::dotProduct(Vector2D vector)
{
	return this->x * vector.x + this->y * vector.y;
}

float Vector2D::magnitude() {

	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Vector2D::normalize() {
	float vectorMagnitude = Vector2D::magnitude();
	if (vectorMagnitude > 0) {
		this->x = this->x / vectorMagnitude;
		this->y = this->y / vectorMagnitude;
	}
}

float Vector2D::getAngleBetweenVectors(Vector2D vector) {
	float angle = atan2(this->x - vector.x, this->y - vector.y);
	angle = angle * (float)(180 / M_PI);
	return angle;
}

void Vector2D::clean()
{
	double epsilon = pow(10, -5);

	if (this->x < epsilon && this->x > -epsilon)
		this->x = 0;

	if (this->y < epsilon && this->y > -epsilon)
		this->y = 0;
}

bool Vector2D::isPerpendicular(Vector2D vector) {
	if (dotProduct(vector) == 0) {
		return true;
	}

	return false;
}

bool Vector2D::hasSameDirection(Vector2D vector) {
	if (dotProduct(vector) > 0) {
		return true;
	}

	return false;
}

bool Vector2D::hasOpDirection(Vector2D vector) {
	if (dotProduct(vector) < 0) {
		return true;
	}

	return false;
}

const float Vector2D::getX() {
	return this->x;
}

const float Vector2D::getY() {
	return this->y;
}

//--------------------------------------------
//--------------------------------------------
//----------------- VECTOR3D -----------------
//--------------------------------------------
//--------------------------------------------


Vector3D::Vector3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D::Vector3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D operator+(const Vector3D& vector1, const Vector3D& vector2) {
	float tempX = vector1.x + vector2.x;
	float tempY = vector1.y + vector2.y;
	float tempZ = vector1.z + vector2.z;
	return Vector3D::Vector3D(tempX, tempY, tempZ);
}

Vector3D operator-(const Vector3D& vector1, const Vector3D& vector2) {
	float tempX = vector1.x - vector2.x;
	float tempY = vector1.y - vector2.y;
	float tempZ = vector1.z - vector2.z;
	return Vector3D::Vector3D(tempX, tempY, tempZ);
}

Vector3D operator-(const Vector3D& vector) {
	return Vector3D::Vector3D(-vector.x, -vector.y, -vector.z);
}

Vector3D operator*(const float& scalar, const Vector3D& vector) {
	float tempX = vector.x * scalar;
	float tempY = vector.y * scalar;
	float tempZ = vector.z * scalar;
	return Vector3D::Vector3D(tempX, tempY, tempZ);
}

Vector3D operator*(const Vector3D& vector, const float& scalar) {
	float tempX = vector.x * scalar;
	float tempY = vector.y * scalar;
	float tempZ = vector.z * scalar;
	return Vector3D::Vector3D(tempX, tempY, tempZ);
}

std::ostream& operator<<(std::ostream& out, const Vector3D& vector) {
	out << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return out;
}

float Vector3D::dotProduct(Vector3D vector)
{
	return this->x * vector.x + this->y * vector.y + this->z * vector.z;
}

Vector3D Vector3D::crossProduct(Vector3D vector)
{
	float tempX = this->y * vector.z - this->z*vector.y;
	float tempY = this->z * vector.x - this->x*vector.z;
	float tempZ = this->x * vector.y - this->y*vector.x;
	return Vector3D::Vector3D(tempX, tempY, tempZ);
}

float Vector3D::magnitude() {

	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

Vector3D Vector3D::normalize() {
	float tempX = 0;
	float tempY = 0;
	float tempZ = 0;

	float vectorMagnitude = Vector3D::magnitude();
	if (vectorMagnitude > 0) {
		tempX = this->x / vectorMagnitude;
		tempY = this->y / vectorMagnitude;
		tempZ = this->z / vectorMagnitude;
	}

	return Vector3D::Vector3D(tempX, tempY, tempZ);
}

void Vector3D::clean()
{
	double epsilon = pow(10, -5);

	if (this->x < epsilon && this->x > -epsilon)
		this->x = 0;

	if (this->y < epsilon && this->y > -epsilon)
		this->y = 0;

	if (this->z < epsilon && this->z > -epsilon)
		this->z = 0;
}

bool Vector3D::isPerpendicular(Vector3D vector) {
	if (dotProduct(vector) == 0) {
		return true;
	}

	return false;
}

float Vector3D::getAngleBetweenVectors(Vector3D vector) {
	float angle = acos((dotProduct(vector)) / (Vector3D::magnitude() * vector.magnitude()));
	angle = angle * (float)(180 / M_PI);
	return angle;
}


bool Vector3D::hasSameDirection(Vector3D vector) {
	if (dotProduct(vector) > 0) {
		return true;
	}

	return false;
}

bool Vector3D::hasOpDirection(Vector3D vector) {
	if (dotProduct(vector) < 0) {
		return true;
	}

	return false;
}
const float Vector3D::getX() {
	return this->x;
}

const float Vector3D::getY() {
	return this->y;
}
const float Vector3D::getZ() {
	return this->z;
}

const float Vector3D::setX(float value) {
	return this->x = value;
}
const float Vector3D::setY(float value) {
	return this->y = value;
}
const float Vector3D::setZ(float value) {
	return this->z = value;
}

Vector4D Vector3D::toVec4()
{
	return Vector4D(x, y, z, 1.0f);
}


//--------------------------------------------
//--------------------------------------------
//----------------- VECTOR4D -----------------
//--------------------------------------------
//--------------------------------------------


Vector4D::Vector4D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Vector4D::Vector4D(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector3D vLerp(Vector3D vi, Vector3D vf, float fraction)
{
	Vector3D vm = (vf - vi) * fraction;
	Vector3D p = vi + vm;
	return p;
}

Vector4D operator+(const Vector4D& vector1, const Vector4D& vector2) {
	float tempX = vector1.x + vector2.x;
	float tempY = vector1.y + vector2.y;
	float tempZ = vector1.z + vector2.z;
	float tempW = vector1.w + vector2.w;
	return Vector4D::Vector4D(tempX, tempY, tempZ, tempW);
}

Vector4D operator-(const Vector4D& vector1, const Vector4D& vector2) {
	float tempX = vector1.x - vector2.x;
	float tempY = vector1.y - vector2.y;
	float tempZ = vector1.z - vector2.z;
	float tempW = vector1.w - vector2.w;
	return Vector4D::Vector4D(tempX, tempY, tempZ, tempW);
}

Vector4D operator-(const Vector4D& vector) {
	return Vector4D::Vector4D(-vector.x, -vector.y, -vector.z, -vector.w);
}

Vector4D operator*(const float& scalar, const Vector4D& vector) {
	float tempX = vector.x * scalar;
	float tempY = vector.y * scalar;
	float tempZ = vector.z * scalar;
	float tempW = vector.w * scalar;
	return Vector4D::Vector4D(tempX, tempY, tempZ, tempW);
}

Vector4D operator*(const Vector4D& vector, const float& scalar) {
	float tempX = vector.x * scalar;
	float tempY = vector.y * scalar;
	float tempZ = vector.z * scalar;
	float tempW = vector.w * scalar;
	return Vector4D::Vector4D(tempX, tempY, tempZ, tempW);
}

std::ostream& operator<<(std::ostream& out, const Vector4D& vector) {
	out << "[" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]";
	return out;
}

float Vector4D::dotProduct(Vector4D vector)
{
	return this->x * vector.x + this->y * vector.y + this->z * vector.z + this->w * vector.w;
}

float Vector4D::magnitude() {

	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
}

void Vector4D::normalize() {
	float vectorMagnitude = Vector4D::magnitude();
	if (vectorMagnitude > 0) {
		this->x = this->x / vectorMagnitude;
		this->y = this->y / vectorMagnitude;
		this->z = this->z / vectorMagnitude;
		this->w = this->w / vectorMagnitude;
	}
}

void Vector4D::clean()
{
	double epsilon = pow(10, -5);

	if (this->x < epsilon && this->x > -epsilon)
		this->x = 0;

	if (this->y < epsilon && this->y > -epsilon)
		this->y = 0;

	if (this->z < epsilon && this->z > -epsilon)
		this->z = 0;

	if (this->w < epsilon && this->w > -epsilon)
		this->w = 0;
}

bool Vector4D::isPerpendicular(Vector4D vector) {
	if (dotProduct(vector) == 0) {
		return true;
	}

	return false;
}

float Vector4D::getAngleBetweenVectors(Vector4D vector) {
	float angle = acos((dotProduct(vector)) / (Vector4D::magnitude() * vector.magnitude()));
	angle = angle * (float)(180 / M_PI);
	return angle;
}


bool Vector4D::hasSameDirection(Vector4D vector) {
	if (dotProduct(vector) > 0) {
		return true;
	}

	return false;
}

bool Vector4D::hasOpDirection(Vector4D vector) {
	if (dotProduct(vector) < 0) {
		return true;
	}

	return false;
}
const float Vector4D::getX() {
	return this->x;
}
const float Vector4D::getY() {
	return this->y;
}
const float Vector4D::getZ() {
	return this->z;
}
const float Vector4D::getW() {
	return this->w;
}

const float Vector4D::setX(float value) {
	return this->x = value;
}
const float Vector4D::setY(float value) {
	return this->y = value;
}
const float Vector4D::setZ(float value) {
	return this->z = value;
}
const float Vector4D::setW(float value) {
	return this->w = value;
}

Vector3D Vector4D::toVec3()
{
	return Vector3D(x, y, z);
}
