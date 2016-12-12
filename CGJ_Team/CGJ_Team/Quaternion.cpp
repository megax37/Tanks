#include "Quaternion.h"

Quaternion::Quaternion() {
	this->t = 1.0f;
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Quaternion::Quaternion(float t, float x, float y, float z) {
	this->t = t;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::Quaternion(float theta, Vector3D axis)
{
	axis.normalize();

	float a = theta * (float)DEGREES_TO_RADIANS;
	this->t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	this->x = axis.x * s;
	this->y = axis.y * s;
	this->z = axis.z * s;

	if (fabs(t) < qThreshold) t = 0.0f;
	if (fabs(x) < qThreshold) x = 0.0f;
	if (fabs(y) < qThreshold) y = 0.0f;
	if (fabs(z) < qThreshold) z = 0.0f;
}

Quaternion::Quaternion(Vector3D vec)
{
	this->t = 0.0f;
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

Quaternion::~Quaternion()
{
}


Quaternion qFromAngleAxis(float theta, Vector3D axisn)
{
	//Vector4D axisn = axis.normalize();
	axisn.normalize();
	Quaternion q;

	float a = theta * (float)DEGREES_TO_RADIANS;
	q.t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	q.x = axisn.getX() * s;
	q.y = axisn.getY() * s;
	q.z = axisn.getZ() * s;

	qClean(q);
	return qNormalize(q);
}

void qToAngleAxis(const Quaternion& q, float& theta, Vector3D& axis)
{
	Quaternion qn = qNormalize(q);
	theta = 2.0f * acos(qn.t) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - qn.t*qn.t);
	if (s < qThreshold) {
		axis.setX(1.0f);
		axis.setY(0.0f);
		axis.setZ(0.0f);
	}
	else {
		axis.setX(qn.x / s);
		axis.setY(qn.y / s);
		axis.setZ(qn.z / s);
	}
}

void qClean(Quaternion& q)
{
	if (fabs(q.t) < qThreshold) q.t = 0.0f;
	if (fabs(q.x) < qThreshold) q.x = 0.0f;
	if (fabs(q.y) < qThreshold) q.y = 0.0f;
	if (fabs(q.z) < qThreshold) q.z = 0.0f;
}

float qQuadrance(const Quaternion& q)
{
	return q.t*q.t + q.x*q.x + q.y*q.y + q.z*q.z;
}

float qNorm(const Quaternion& q)
{
	return sqrt(qQuadrance(q));
}

Quaternion qNormalize(const Quaternion& q)
{
	float s = 1 / qNorm(q);
	return qMultiply(q, s);
}

Quaternion qConjugate(const Quaternion& q)
{
	Quaternion qconj = { q.t, -q.x, -q.y, -q.z };
	return qconj;
}

Quaternion qInverse(const Quaternion& q)
{
	return qMultiply(qConjugate(q), 1.0f / qQuadrance(q));
}

Quaternion qAdd(const Quaternion& q0, const Quaternion& q1)
{
	Quaternion q;
	q.t = q0.t + q1.t;
	q.x = q0.x + q1.x;
	q.y = q0.y + q1.y;
	q.z = q0.z + q1.z;
	return q;
}

Quaternion qMultiply(const Quaternion& q, const float s)
{
	Quaternion sq;
	sq.t = s * q.t;
	sq.x = s * q.x;
	sq.y = s * q.y;
	sq.z = s * q.z;
	return sq;
}

Quaternion operator*(const Quaternion& q0, const Quaternion& q1) {
	Quaternion q;
	q.t = q0.t * q1.t - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	q.x = q0.t * q1.x + q0.x * q1.t + q0.y * q1.z - q0.z * q1.y;
	q.y = q0.t * q1.y + q0.y * q1.t + q0.z * q1.x - q0.x * q1.z;
	q.z = q0.t * q1.z + q0.z * q1.t + q0.x * q1.y - q0.y * q1.x;
	return q;
}

Quaternion qMultiply(const Quaternion& q0, const Quaternion& q1)
{
	Quaternion q;
	q.t = q0.t * q1.t - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	q.x = q0.t * q1.x + q0.x * q1.t + q0.y * q1.z - q0.z * q1.y;
	q.y = q0.t * q1.y + q0.y * q1.t + q0.z * q1.x - q0.x * q1.z;
	q.z = q0.t * q1.z + q0.z * q1.t + q0.x * q1.y - q0.y * q1.x;
	return q;
}

Matrix4D qGLMatrix(const Quaternion& q) {
	Quaternion qn = qNormalize(q);
	
	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;

	Matrix4D matrix = Matrix4D(
		1.0f - 2.0f * (yy + zz),  2.0f * (xy + zt),  2.0f * (xz - yt), 0.0f,
		2.0f * (xy - zt),  1.0f - 2.0f * (xx + zz),  2.0f * (yz + xt), 0.0f,
		2.0f * (xz + yt),  2.0f * (yz - xt),  1.0f - 2.0f * (xx + yy), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	/*matrix.m[0][0] = 1.0f - 2.0f * (yy + zz);
	matrix.m[1][0] = 2.0f * (xy + zt);
	matrix.m[2][0] = 2.0f * (xz - yt);
	matrix.m[3][0] = 0.0f;

	matrix.m[0][1] = 2.0f * (xy - zt);
	matrix.m[1][1] = 1.0f - 2.0f * (xx + zz);
	matrix.m[2][1] = 2.0f * (yz + xt);
	matrix.m[3][1] = 0.0f;

	matrix.m[0][2] = 2.0f * (xz + yt);
	matrix.m[1][2] = 2.0f * (yz - xt);
	matrix.m[2][2] = 1.0f - 2.0f * (xx + yy);
	matrix.m[3][2] = 0.0f;

	matrix.m[0][3] = 0.0f;
	matrix.m[1][3] = 0.0f;
	matrix.m[2][3] = 0.0f;
	matrix.m[3][3] = 1.0f;*/

	matrix.clean();

	return matrix;
}

Quaternion qLerp(const Quaternion& q0, const Quaternion& q1, float k)
{
	float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	Quaternion qi = qAdd(qMultiply(q0, k0), qMultiply(q1, k1));
	return qNormalize(qi);
}

Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k)
{
	float angle = acos(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
	if (angle == 0.0f) return q0;
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	Quaternion qi = qAdd(qMultiply(q0, k0), qMultiply(q1, k1));
	return qNormalize(qi);
}

bool qEqual(const Quaternion& q0, const Quaternion& q1)
{
	return (fabs(q0.t - q1.t) < qThreshold && fabs(q0.x - q1.x) < qThreshold &&
		fabs(q0.y - q1.y) < qThreshold && fabs(q0.z - q1.z) < qThreshold);
}

void qPrint(const std::string& s, const Quaternion& q)
{
	std::cout << s.c_str() << " = (" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")" << std::endl;
}

void qPrintAngleAxis(const std::string& s, const Quaternion& q)
{
	std::cout << s.c_str() << " = [" << std::endl;

	float thetaf;
	Vector3D axis_f;
	qToAngleAxis(q, thetaf, axis_f);
	std::cout << "  angle = " << thetaf << std::endl;
	std::cout << axis_f << std::endl;
	std::cout << "]" << std::endl;
}
