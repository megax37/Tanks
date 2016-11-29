#ifndef _MATRIX_FACTORY_
#define _MATRIX_FACTORY_

//#include "engine.h"
#include "VectorFactory.h"
//#include "Quaternion.h"
#include <vector>

class Matrix3D;
class Matrix4D;
class Quaternion;

class Matrix2D {

public:

	Matrix2D();
	Matrix2D(float a, float b, float c, float d);
	~Matrix2D();

	friend std::ostream& operator<<(std::ostream& out, const Matrix2D& matrix);

	friend Matrix2D operator+(const Matrix2D&, const Matrix2D&);

	friend Matrix2D operator-(const Matrix2D&, const Matrix2D&);
	friend Matrix2D operator-(const Matrix2D&);

	friend Matrix2D operator*(const float&, const Matrix2D&);
	friend Matrix2D operator*(const Matrix2D&, const float&);
	friend Matrix2D operator*(const Matrix2D&, const Matrix2D&);
	friend Vector2D operator*(const Matrix2D&, Vector2D);
	friend Vector2D operator*(Vector2D, const Matrix2D&);

	Matrix2D transpose();
	float determinant();
	Matrix2D inverse();

	Matrix2D identity();

	Matrix3D toMat3();
	Matrix4D toMat4();

	std::vector<float> toColumnMatrix();

private:

	float m[2][2];

};

class Matrix3D {

public:

	Matrix3D();
	Matrix3D(
		float a, float b, float c,
		float d, float e, float f,
		float g, float h, float i);
	~Matrix3D();

	friend std::ostream& operator<<(std::ostream& out, const Matrix3D& matrix);

	friend Matrix3D operator+(const Matrix3D&, const Matrix3D&);

	friend Matrix3D operator-(const Matrix3D&, const Matrix3D&);
	friend Matrix3D operator-(const Matrix3D&);

	friend Matrix3D operator*(const float&, const Matrix3D&);
	friend Matrix3D operator*(const Matrix3D&, const float&);
	friend Matrix3D operator*(const Matrix3D&, const Matrix3D&);
	friend Vector3D operator*(const Matrix3D&, Vector3D);
	friend Vector3D operator*(Vector3D, const Matrix3D&);

	Matrix3D transpose();
	float determinant();
	Matrix3D inverse();

	Matrix3D identity();

	Matrix2D toMat2();
	Matrix4D toMat4();

	std::vector<float> toColumnMatrix();

private:

	float m[3][3];

};

Matrix4D identity();

Matrix4D translation(float x, float y, float z);
Matrix4D translation(Vector3D pos);
Matrix4D rotation(float angle, float x, float y, float z);
Matrix4D rotation(float angle, Vector3D axis);
Matrix4D rotation(Quaternion q);
Matrix4D scale(float x, float y, float z);

Matrix4D lookAt(Vector3D eye, Vector3D center, Vector3D up);
Matrix4D orthographicMatrix(float left, float right, float bottom, float top, float nearr, float farr);
Matrix4D perspectiveMatrix(float fovy, float aspect, float nearZ, float farZ);

class Matrix4D {

public:

	Matrix4D();
	Matrix4D(
		float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p);
	~Matrix4D();



	friend std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix);

	friend Matrix4D operator+(const Matrix4D&, const Matrix4D&);

	friend Matrix4D operator-(const Matrix4D&, const Matrix4D&);
	friend Matrix4D operator-(const Matrix4D&);

	friend Matrix4D operator*(const float&, const Matrix4D&);
	friend Matrix4D operator*(const Matrix4D&, const float&);
	friend Matrix4D operator*(const Matrix4D&, const Matrix4D&);
	friend Vector4D operator*(const Matrix4D&, Vector4D);
	friend Vector4D operator*(Vector4D, const Matrix4D&);

	friend std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix);

	Matrix4D transpose();
	float determinant();
	Matrix4D inverse();

	void clean();

	Matrix2D toMat2();
	Matrix3D toMat3();

	std::vector<float> toColumnMatrix();
	std::vector<float> toMatrix16();

private:

	float m[4][4];
};
#endif
