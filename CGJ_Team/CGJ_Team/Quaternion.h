#ifndef _QUATERNION_
#define _QUATERNION_

#include "MatrixFactory.h"

const float qThreshold = (float)1.0e-5;

class Quaternion {

public:

	Quaternion();
	Quaternion(float t, float x, float y, float z);
	Quaternion(float theta, Vector3D axis);
	~Quaternion();

	friend Quaternion operator*(const Quaternion&, const Quaternion&);

	float t, x, y, z;	
};

Quaternion qFromAngleAxis(float theta, Vector3D axis);
void qToAngleAxis(const Quaternion& q, float& theta, Vector3D& axis);
void qClean(Quaternion& q);
float qQuadrance(const Quaternion& q);
float qNorm(const Quaternion& q);
Quaternion qNormalize(const Quaternion& q);
Quaternion qConjugate(const Quaternion& q);
Quaternion qInverse(const Quaternion& q);
Quaternion qAdd(const Quaternion& q0, const Quaternion& q1);
Quaternion qMultiply(const Quaternion& q, const float s);
Quaternion qMultiply(const Quaternion& q0, const Quaternion& q1);

Matrix4D qGLMatrix(const Quaternion& q);

Quaternion qLerp(const Quaternion& q0, const Quaternion& q1, float k);
Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k);
bool qEqual(const Quaternion& q0, const Quaternion& q1);
void qPrint(const std::string& s, const Quaternion& q);
void qPrintAngleAxis(const std::string& s, const Quaternion& q);

#endif