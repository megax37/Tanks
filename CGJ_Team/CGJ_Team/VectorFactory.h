#ifndef _VECTOR_FACTORY_
#define _VECTOR_FACTORY_

//#include "engine.h"
#include <iostream>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

class Vector2D {

public:

	Vector2D();
	Vector2D(float x, float y);

	friend Vector2D operator+(const Vector2D&, const Vector2D&);

	friend Vector2D operator-(const Vector2D&, const Vector2D&);
	friend Vector2D operator-(const Vector2D&);

	friend Vector2D operator*(const float&, const Vector2D&);
	friend Vector2D operator*(const Vector2D&, const float&);

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vector);

	float dotProduct(Vector2D vector);

	float magnitude();
	void normalize();

	float getAngleBetweenVectors(Vector2D vector);

	void clean();

	bool isPerpendicular(Vector2D vector);
	bool hasSameDirection(Vector2D vector);
	bool hasOpDirection(Vector2D vector);

	const float getX();
	const float getY();

	float x, y;

private:

};


class Vector3D {

public:

	Vector3D();
	Vector3D(float x, float y, float z);

	friend Vector3D operator+(const Vector3D&, const Vector3D&);

	friend Vector3D operator-(const Vector3D&, const Vector3D&);
	friend Vector3D operator-(const Vector3D&);

	friend Vector3D operator*(const float&, const Vector3D&);
	friend Vector3D operator*(const Vector3D&, const float&);

	friend std::ostream& operator<<(std::ostream& out, const Vector3D& vector);

	float dotProduct(Vector3D vector);
	Vector3D crossProduct(Vector3D vector);

	float magnitude();
	Vector3D normalize();

	void clean();

	float getAngleBetweenVectors(Vector3D vector);

	bool isPerpendicular(Vector3D vector);
	bool hasSameDirection(Vector3D vector);
	bool hasOpDirection(Vector3D vector);

	const float getX();
	const float getY();
	const float getZ();

	const float setX(float value);
	const float setY(float value);
	const float setZ(float value);

	float x, y, z;

private:

};

Vector3D vLerp(Vector3D vi, Vector3D vf, float fraction);

class Vector4D {

public:

	Vector4D();
	Vector4D(float x, float y, float z, float w);

	friend Vector4D operator+(const Vector4D&, const Vector4D&);

	friend Vector4D operator-(const Vector4D&, const Vector4D&);
	friend Vector4D operator-(const Vector4D&);

	friend Vector4D operator*(const float&, const Vector4D&);
	friend Vector4D operator*(const Vector4D&, const float&);

	friend std::ostream& operator<<(std::ostream& out, const Vector4D& vector);

	float dotProduct(Vector4D vector);

	float magnitude();
	void normalize();

	void clean();

	float getAngleBetweenVectors(Vector4D vector);

	bool isPerpendicular(Vector4D vector);
	bool hasSameDirection(Vector4D vector);
	bool hasOpDirection(Vector4D vector);

	const float getX();
	const float getY();
	const float getZ();
	const float getW();

	const float setX(float value);
	const float setY(float value);
	const float setZ(float value);
	const float setW(float value);

	float x, y, z, w;

private:

};

#endif
