#define _USE_MATH_DEFINES

#include "MatrixFactory.h"
#include "Quaternion.h"

//--------------------------------------------
//--------------------------------------------
//----------------- MATRIX2D -----------------
//--------------------------------------------
//--------------------------------------------


Matrix2D::Matrix2D() {
	this->m[0][0] = 0;
	this->m[0][1] = 0;
	this->m[1][0] = 0;
	this->m[1][1] = 0;
}

Matrix2D::Matrix2D(float a, float b, float c, float d) {
	this->m[0][0] = a;
	this->m[0][1] = b;
	this->m[1][0] = c;
	this->m[1][1] = d;
}

Matrix2D::~Matrix2D() {

}


std::ostream& operator<<(std::ostream& out, const Matrix2D& matrix) {
	out << "|" << matrix.m[0][0] << " " << matrix.m[0][1] << "|" << std::endl << "|" << matrix.m[1][0] << " " << matrix.m[1][1] << "|" << std::endl;
	return out;
}

Matrix2D operator+(const Matrix2D& matrix1, const Matrix2D& matrix2) {
	return Matrix2D::Matrix2D(
		matrix1.m[0][0] + matrix2.m[0][0],
		matrix1.m[0][1] + matrix2.m[0][1],
		matrix1.m[1][0] + matrix2.m[1][0],
		matrix1.m[1][1] + matrix2.m[1][1]
		);
}

Matrix2D operator-(const Matrix2D& matrix1, const Matrix2D& matrix2) {
	return Matrix2D::Matrix2D(
		matrix1.m[0][0] - matrix2.m[0][0],
		matrix1.m[0][1] - matrix2.m[0][1],
		matrix1.m[1][0] - matrix2.m[1][0],
		matrix1.m[1][1] - matrix2.m[1][1]
		);
}

Matrix2D operator-(const Matrix2D& matrix1) {
	return Matrix2D::Matrix2D(-matrix1.m[0][0], -matrix1.m[0][1], -matrix1.m[1][0], -matrix1.m[1][1]);
}

Matrix2D operator*(const float& scalar, const Matrix2D& matrix) {
	return Matrix2D::Matrix2D(matrix.m[0][0] * scalar, matrix.m[0][1] * scalar, matrix.m[1][0] * scalar, matrix.m[1][1] * scalar);
}

Matrix2D operator*(const Matrix2D& matrix, const float& scalar) {
	return Matrix2D::Matrix2D(matrix.m[0][0] * scalar, matrix.m[0][1] * scalar, matrix.m[1][0] * scalar, matrix.m[1][1] * scalar);
}

Matrix2D operator*(const Matrix2D& matrix1, const Matrix2D& matrix2) {
	return Matrix2D::Matrix2D(
		matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0],
		matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1],
		matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0],
		matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1]
		);
}

Vector2D operator*(const Matrix2D& matrix, Vector2D vector) {
	return Vector2D(
		matrix.m[0][0] * vector.getX() + matrix.m[0][1] * vector.getY(),
		matrix.m[1][0] * vector.getX() + matrix.m[1][1] * vector.getY());
}

Vector2D operator*(Vector2D vector, const Matrix2D& matrix) {
	return Vector2D(
		matrix.m[0][0] * vector.getX() + matrix.m[0][1] * vector.getY(),
		matrix.m[1][0] * vector.getX() + matrix.m[1][1] * vector.getY());
}


Matrix2D Matrix2D::transpose() {
	Matrix2D transpost = Matrix2D();

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			transpost.m[j][i] = this->m[i][j];
		}
	}

	return transpost;
}

float Matrix2D::determinant() {
	return ((this->m[0][0] * this->m[1][1]) - (this->m[0][1] * this->m[1][0]));
}

Matrix2D Matrix2D::inverse() {
	float determinant =  this->determinant();
	if(determinant != 0)
		return (1.0f / determinant) * Matrix2D(this->m[1][1], -this->m[0][1], -this->m[1][0], this->m[0][0]);

	exit(EXIT_FAILURE);
}

Matrix2D Matrix2D::identity() {
	return Matrix2D(
		1.0f, 0.0f,
		0.0f, 1.0f);
}

Matrix3D Matrix2D::toMat3()
{
	return Matrix3D(
		this->m[0][0], this->m[0][1], 0,
		this->m[1][0], this->m[1][1], 0,
		0, 0, 1);
}

Matrix4D Matrix2D::toMat4()
{
	return Matrix4D(
		this->m[0][0], this->m[0][1], 0, 0,
		this->m[1][0], this->m[1][1], 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

std::vector<float> Matrix2D::toColumnMatrix()
{
	std::vector<float> columnMajorMatrix(4);
	int index;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 2; i++) {
			index = j * 2 + i;
			columnMajorMatrix.at(index) = this->m[i][j];
		}
	}

	return columnMajorMatrix;
}


//--------------------------------------------
//--------------------------------------------
//----------------- MATRIX3D -----------------
//--------------------------------------------
//--------------------------------------------


Matrix3D::Matrix3D() {
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			this->m[x][y] = 0;
		}
	}
}

Matrix3D::Matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
	this->m[0][0] = a;
	this->m[0][1] = b;
	this->m[0][2] = c;

	this->m[1][0] = d;
	this->m[1][1] = e;
	this->m[1][2] = f;

	this->m[2][0] = g;
	this->m[2][1] = h;
	this->m[2][2] = i;
}

Matrix3D::~Matrix3D() {

}


std::ostream& operator<<(std::ostream& out, const Matrix3D& matrix) {
	out << "|" << matrix.m[0][0] << " " << matrix.m[0][1] << " " << matrix.m[0][2] << "|" << std::endl
		<< "|" << matrix.m[1][0] << " " << matrix.m[1][1] << " " << matrix.m[1][2] << "|" << std::endl
		<< "|" << matrix.m[2][0] << " " << matrix.m[2][1] << " " << matrix.m[2][2] << "|" << std::endl;

	return out;
}

Matrix3D operator+(const Matrix3D& matrix1, const Matrix3D& matrix2) {
	return Matrix3D::Matrix3D(
		matrix1.m[0][0] + matrix2.m[0][0], matrix1.m[0][1] + matrix2.m[0][1], matrix1.m[0][2] + matrix2.m[0][2],
		matrix1.m[1][0] + matrix2.m[1][0], matrix1.m[1][1] + matrix2.m[1][1], matrix1.m[1][2] + matrix2.m[1][2],
		matrix1.m[2][0] + matrix2.m[2][0], matrix1.m[2][1] + matrix2.m[2][1], matrix1.m[2][2] + matrix2.m[2][2]
		);
}

Matrix3D operator-(const Matrix3D& matrix1, const Matrix3D& matrix2) {
	return Matrix3D::Matrix3D(
		matrix1.m[0][0] - matrix2.m[0][0], matrix1.m[0][1] - matrix2.m[0][1], matrix1.m[0][2] - matrix2.m[0][2],
		matrix1.m[1][0] - matrix2.m[1][0], matrix1.m[1][1] - matrix2.m[1][1], matrix1.m[1][2] - matrix2.m[1][2],
		matrix1.m[2][0] - matrix2.m[2][0], matrix1.m[2][1] - matrix2.m[2][1], matrix1.m[2][2] - matrix2.m[2][2]
		);
}

Matrix3D operator-(const Matrix3D& matrix1) {
	return Matrix3D::Matrix3D(
		-matrix1.m[0][0], -matrix1.m[0][1], -matrix1.m[0][2],
		-matrix1.m[1][0], -matrix1.m[1][1], -matrix1.m[1][2],
		-matrix1.m[2][0], -matrix1.m[2][1], -matrix1.m[2][2]
		);
}

Matrix3D operator*(const float& scalar, const Matrix3D& matrix) {
	return Matrix3D::Matrix3D(
		matrix.m[0][0] * scalar, matrix.m[0][1] * scalar, matrix.m[0][2] * scalar,
		matrix.m[1][0] * scalar, matrix.m[1][1] * scalar, matrix.m[1][2] * scalar,
		matrix.m[2][0] * scalar, matrix.m[2][1] * scalar, matrix.m[2][2] * scalar);
}

Matrix3D operator*(const Matrix3D& matrix, const float& scalar) {
	return Matrix3D::Matrix3D(
		matrix.m[0][0] * scalar, matrix.m[0][1] * scalar, matrix.m[0][2] * scalar,
		matrix.m[1][0] * scalar, matrix.m[1][1] * scalar, matrix.m[1][2] * scalar,
		matrix.m[2][0] * scalar, matrix.m[2][1] * scalar, matrix.m[2][2] * scalar);
}

Matrix3D operator*(const Matrix3D& matrix1, const Matrix3D& matrix2) {
	return Matrix3D::Matrix3D(
		matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0],
		matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1],
		matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2],

		matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0],
		matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1],
		matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2],

		matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0],
		matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1],
		matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2]
		);
}

Vector3D operator*(const Matrix3D& matrix, Vector3D vector) {
	return Vector3D(
		matrix.m[0][0] * vector.getX() + matrix.m[0][1] * vector.getY() + matrix.m[0][2] * vector.getZ(),
		matrix.m[1][0] * vector.getX() + matrix.m[1][1] * vector.getY() + matrix.m[1][2] * vector.getZ(),
		matrix.m[2][0] * vector.getX() + matrix.m[2][1] * vector.getY() + matrix.m[2][2] * vector.getZ());
}

Vector3D operator*(Vector3D vector, const Matrix3D& matrix) {
	return Vector3D(
		matrix.m[0][0] * vector.getX() + matrix.m[0][1] * vector.getY() + matrix.m[0][2] * vector.getZ(),
		matrix.m[1][0] * vector.getX() + matrix.m[1][1] * vector.getY() + matrix.m[1][2] * vector.getZ(),
		matrix.m[2][0] * vector.getX() + matrix.m[2][1] * vector.getY() + matrix.m[2][2] * vector.getZ());
}


Matrix3D Matrix3D::transpose() {
	Matrix3D transpost = Matrix3D();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			transpost.m[j][i] = this->m[i][j];
		}
	}

	return transpost;
}

float Matrix3D::determinant() {
	return (
		(this->m[0][0] * this->m[1][1] * this->m[2][2]) +
		(this->m[0][1] * this->m[1][2] * this->m[2][0]) +
		(this->m[0][2] * this->m[1][0] * this->m[2][1]) -
		(this->m[0][2] * this->m[1][1] * this->m[2][0]) -
		(this->m[0][1] * this->m[1][0] * this->m[2][2]) -
		(this->m[0][0] * this->m[1][2] * this->m[2][1])
		);
}


Matrix3D Matrix3D::inverse() {
	float determinant = this->determinant();

	if (determinant != 0) {

		float invertDeterminant = 1.0f / determinant;

		float result0 = (this->m[1][1] * this->m[2][2] - this->m[2][1] * this->m[1][2]) * invertDeterminant;
		float result1 = -(this->m[0][1] * this->m[2][2] - this->m[0][2] * this->m[2][1]) * invertDeterminant;
		float result2 = (this->m[0][1] * this->m[1][2] - this->m[0][2] * this->m[1][1]) * invertDeterminant;
		float result3 = -(this->m[1][0] * this->m[2][2] - this->m[1][2] * this->m[2][0]) * invertDeterminant;
		float result4 = (this->m[0][0] * this->m[2][2] - this->m[0][2] * this->m[2][0]) * invertDeterminant;
		float result5 = -(this->m[0][0] * this->m[1][2] - this->m[1][0] * this->m[0][2]) * invertDeterminant;
		float result6 = (this->m[1][0] * this->m[2][1] - this->m[2][0] * this->m[1][1]) * invertDeterminant;
		float result7 = -(this->m[0][0] * this->m[2][1] - this->m[2][0] * this->m[0][1]) * invertDeterminant;
		float result8 = (this->m[0][0] * this->m[1][1] - this->m[1][0] * this->m[0][1]) * invertDeterminant;

		return Matrix3D(result0, result1, result2, result3, result4, result5, result6, result7, result8);
	}
	//ADD mensagem de erro
	exit(EXIT_FAILURE);
}

Matrix3D Matrix3D::identity() {
	return Matrix3D(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix2D Matrix3D::toMat2()
{
	return Matrix2D(
		this->m[0][0], this->m[0][1],
		this->m[1][0], this->m[1][1]);
}

Matrix4D Matrix3D::toMat4()
{
	return Matrix4D(
		this->m[0][0], this->m[0][1], this->m[0][2], 0,
		this->m[1][0], this->m[1][1], this->m[1][2], 0,
		this->m[2][0], this->m[2][1], this->m[2][2], 0,
		0, 0, 0, 1);
}

std::vector<float> Matrix3D::toColumnMatrix()
{
	std::vector<float> columnMajorMatrix(9);
	int index;

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			index = j * 3 + i;
			columnMajorMatrix.at(index) = this->m[i][j];
		}
	}

	return columnMajorMatrix;
}

//--------------------------------------------
//--------------------------------------------
//----------------- MATRIX4D -----------------
//--------------------------------------------
//--------------------------------------------

Matrix4D::Matrix4D() {

	this->m[0][0] = 0;
	this->m[0][1] = 0;
	this->m[0][2] = 0;
	this->m[0][3] = 0;

	this->m[1][0] = 0;
	this->m[1][1] = 0;
	this->m[1][2] = 0;
	this->m[1][3] = 0;

	this->m[2][0] = 0;
	this->m[2][1] = 0;
	this->m[2][2] = 0;
	this->m[2][3] = 0;

	this->m[3][0] = 0;
	this->m[3][1] = 0;
	this->m[3][2] = 0;
	this->m[3][3] = 0;

}

Matrix4D::Matrix4D(
	float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p) {

	this->m[0][0] = a;
	this->m[0][1] = b;
	this->m[0][2] = c;
	this->m[0][3] = d;

	this->m[1][0] = e;
	this->m[1][1] = f;
	this->m[1][2] = g;
	this->m[1][3] = h;

	this->m[2][0] = i;
	this->m[2][1] = j;
	this->m[2][2] = k;
	this->m[2][3] = l;

	this->m[3][0] = m;
	this->m[3][1] = n;
	this->m[3][2] = o;
	this->m[3][3] = p;

}

Matrix4D::~Matrix4D() {

}


std::ostream& operator<<(std::ostream& out, const Matrix4D& matrix) {
	out << "|" << matrix.m[0][0] << " " << matrix.m[0][1] << " " << matrix.m[0][2] << " " << matrix.m[0][3] << "|" << std::endl
		<< "|" << matrix.m[1][0] << " " << matrix.m[1][1] << " " << matrix.m[1][2] << " " << matrix.m[1][3] << "|" << std::endl
		<< "|" << matrix.m[2][0] << " " << matrix.m[2][1] << " " << matrix.m[2][2] << " " << matrix.m[2][3] << "|" << std::endl
		<< "|" << matrix.m[3][0] << " " << matrix.m[3][1] << " " << matrix.m[3][2] << " " << matrix.m[3][3] << "|" << std::endl;
	return out;
}


Matrix4D operator+(const Matrix4D& matrix1, const Matrix4D& matrix2) {
	return Matrix4D::Matrix4D(
		matrix1.m[0][0] + matrix2.m[0][0], matrix1.m[0][1] + matrix2.m[0][1], matrix1.m[0][2] + matrix2.m[0][2], matrix1.m[0][3] + matrix2.m[0][3],
		matrix1.m[1][0] + matrix2.m[1][0], matrix1.m[1][1] + matrix2.m[1][1], matrix1.m[1][2] + matrix2.m[1][2], matrix1.m[1][3] + matrix2.m[1][3],
		matrix1.m[2][0] + matrix2.m[2][0], matrix1.m[2][1] + matrix2.m[2][1], matrix1.m[2][2] + matrix2.m[2][2], matrix1.m[2][3] + matrix2.m[2][3],
		matrix1.m[3][0] + matrix2.m[3][0], matrix1.m[3][1] + matrix2.m[3][1], matrix1.m[3][2] + matrix2.m[3][2], matrix1.m[3][3] + matrix2.m[3][3]
		);
}

Matrix4D operator-(const Matrix4D& matrix1, const Matrix4D& matrix2) {
	return Matrix4D::Matrix4D(
		matrix1.m[0][0] - matrix2.m[0][0], matrix1.m[0][1] - matrix2.m[0][1], matrix1.m[0][2] - matrix2.m[0][2], matrix1.m[0][3] - matrix2.m[0][3],
		matrix1.m[1][0] - matrix2.m[1][0], matrix1.m[1][1] - matrix2.m[1][1], matrix1.m[1][2] - matrix2.m[1][2], matrix1.m[1][3] - matrix2.m[1][3],
		matrix1.m[2][0] - matrix2.m[2][0], matrix1.m[2][1] - matrix2.m[2][1], matrix1.m[2][2] - matrix2.m[2][2], matrix1.m[2][3] - matrix2.m[2][3],
		matrix1.m[3][0] - matrix2.m[3][0], matrix1.m[3][1] - matrix2.m[3][1], matrix1.m[3][2] - matrix2.m[3][2], matrix1.m[3][3] - matrix2.m[3][3]
		);
}

Matrix4D operator-(const Matrix4D& matrix) {
	return Matrix4D::Matrix4D(
		-matrix.m[0][0], -matrix.m[0][1], -matrix.m[0][2], -matrix.m[0][3],
		-matrix.m[1][0], -matrix.m[1][1], -matrix.m[1][2], -matrix.m[1][3],
		-matrix.m[2][0], -matrix.m[2][1], -matrix.m[2][2], -matrix.m[2][3],
		-matrix.m[3][0], -matrix.m[3][1], -matrix.m[3][2], -matrix.m[3][3]
		);
}

Matrix4D operator*(const float& scalar, const Matrix4D& matrix) {
	return Matrix4D::Matrix4D(
		matrix.m[0][0] * scalar, matrix.m[0][1] * scalar, matrix.m[0][2] * scalar, matrix.m[0][3] * scalar,
		matrix.m[1][0] * scalar, matrix.m[1][1] * scalar, matrix.m[1][2] * scalar, matrix.m[1][3] * scalar,
		matrix.m[2][0] * scalar, matrix.m[2][1] * scalar, matrix.m[2][2] * scalar, matrix.m[2][3] * scalar,
		matrix.m[3][0] * scalar, matrix.m[3][1] * scalar, matrix.m[3][2] * scalar, matrix.m[3][3] * scalar);
}

Matrix4D operator*(const Matrix4D& matrix, const float& scalar) {
	return Matrix4D::Matrix4D(
		matrix.m[0][0] * scalar, matrix.m[0][1] * scalar, matrix.m[0][2] * scalar, matrix.m[0][3] * scalar,
		matrix.m[1][0] * scalar, matrix.m[1][1] * scalar, matrix.m[1][2] * scalar, matrix.m[1][3] * scalar,
		matrix.m[2][0] * scalar, matrix.m[2][1] * scalar, matrix.m[2][2] * scalar, matrix.m[2][3] * scalar,
		matrix.m[3][0] * scalar, matrix.m[3][1] * scalar, matrix.m[3][2] * scalar, matrix.m[3][3] * scalar);
}

Matrix4D operator*(const Matrix4D& matrix1, const Matrix4D& matrix2) {
	return Matrix4D::Matrix4D(
		matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0] + matrix1.m[0][3] * matrix2.m[3][0],
		matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1] + matrix1.m[0][3] * matrix2.m[3][1],
		matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2] + matrix1.m[0][3] * matrix2.m[3][2],
		matrix1.m[0][0] * matrix2.m[0][3] + matrix1.m[0][1] * matrix2.m[1][3] + matrix1.m[0][2] * matrix2.m[2][3] + matrix1.m[0][3] * matrix2.m[3][3],

		matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0] + matrix1.m[1][3] * matrix2.m[3][0],
		matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1] + matrix1.m[1][3] * matrix2.m[3][1],
		matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2] + matrix1.m[1][3] * matrix2.m[3][2],
		matrix1.m[1][0] * matrix2.m[0][3] + matrix1.m[1][1] * matrix2.m[1][3] + matrix1.m[1][2] * matrix2.m[2][3] + matrix1.m[1][3] * matrix2.m[3][3],

		matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0] + matrix1.m[2][3] * matrix2.m[3][0],
		matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1] + matrix1.m[2][3] * matrix2.m[3][1],
		matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2] + matrix1.m[2][3] * matrix2.m[3][2],
		matrix1.m[2][0] * matrix2.m[0][3] + matrix1.m[2][1] * matrix2.m[1][3] + matrix1.m[2][2] * matrix2.m[2][3] + matrix1.m[2][3] * matrix2.m[3][3],

		matrix1.m[3][0] * matrix2.m[0][0] + matrix1.m[3][1] * matrix2.m[1][0] + matrix1.m[3][2] * matrix2.m[2][0] + matrix1.m[3][3] * matrix2.m[3][0],
		matrix1.m[3][0] * matrix2.m[0][1] + matrix1.m[3][1] * matrix2.m[1][1] + matrix1.m[3][2] * matrix2.m[2][1] + matrix1.m[3][3] * matrix2.m[3][1],
		matrix1.m[3][0] * matrix2.m[0][2] + matrix1.m[3][1] * matrix2.m[1][2] + matrix1.m[3][2] * matrix2.m[2][2] + matrix1.m[3][3] * matrix2.m[3][2],
		matrix1.m[3][0] * matrix2.m[0][3] + matrix1.m[3][1] * matrix2.m[1][3] + matrix1.m[3][2] * matrix2.m[2][3] + matrix1.m[3][3] * matrix2.m[3][3]
		);
}

Vector4D operator*(const Matrix4D& matrix, Vector4D vector) {
	return Vector4D(
		matrix.m[0][0] * vector.getX() + matrix.m[0][1] * vector.getY() + matrix.m[0][2] * vector.getZ() + matrix.m[0][3] * vector.getW(),
		matrix.m[1][0] * vector.getX() + matrix.m[1][1] * vector.getY() + matrix.m[1][2] * vector.getZ() + matrix.m[1][3] * vector.getW(),
		matrix.m[2][0] * vector.getX() + matrix.m[2][1] * vector.getY() + matrix.m[2][2] * vector.getZ() + matrix.m[2][3] * vector.getW(),
		matrix.m[3][0] * vector.getX() + matrix.m[3][1] * vector.getY() + matrix.m[3][2] * vector.getZ() + matrix.m[3][3] * vector.getW());
}


Vector4D operator*(Vector4D vector, const Matrix4D& matrix) {
	return Vector4D(
		matrix.m[0][0] * vector.getX() + matrix.m[0][1] * vector.getY() + matrix.m[0][2] * vector.getZ() + matrix.m[0][3] * vector.getW(),
		matrix.m[1][0] * vector.getX() + matrix.m[1][1] * vector.getY() + matrix.m[1][2] * vector.getZ() + matrix.m[1][3] * vector.getW(),
		matrix.m[2][0] * vector.getX() + matrix.m[2][1] * vector.getY() + matrix.m[2][2] * vector.getZ() + matrix.m[2][3] * vector.getW(),
		matrix.m[3][0] * vector.getX() + matrix.m[3][1] * vector.getY() + matrix.m[3][2] * vector.getZ() + matrix.m[3][3] * vector.getW());
}


Matrix4D Matrix4D::transpose() {
	Matrix4D transpost = Matrix4D();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transpost.m[j][i] = this->m[i][j];
		}
	}

	return transpost;
}


float Matrix4D::determinant() {

	float determinant =
		this->m[0][3] * this->m[1][2] * this->m[2][1] * this->m[3][0] - this->m[0][2] * this->m[1][3] * this->m[2][1] * this->m[3][0] -
		this->m[0][3] * this->m[1][1] * this->m[2][2] * this->m[3][0] + this->m[0][1] * this->m[1][3] * this->m[2][2] * this->m[3][0] +
		this->m[0][2] * this->m[1][1] * this->m[2][3] * this->m[3][0] - this->m[0][1] * this->m[1][2] * this->m[2][3] * this->m[3][0] -
		this->m[0][3] * this->m[1][2] * this->m[2][0] * this->m[3][1] + this->m[0][2] * this->m[1][3] * this->m[2][0] * this->m[3][1] +
		this->m[0][3] * this->m[1][0] * this->m[2][2] * this->m[3][1] - this->m[0][0] * this->m[1][3] * this->m[2][2] * this->m[3][1] -
		this->m[0][2] * this->m[1][0] * this->m[2][3] * this->m[3][1] + this->m[0][0] * this->m[1][2] * this->m[2][3] * this->m[3][1] +
		this->m[0][3] * this->m[1][1] * this->m[2][0] * this->m[3][2] - this->m[0][1] * this->m[1][3] * this->m[2][0] * this->m[3][2] -
		this->m[0][3] * this->m[1][0] * this->m[2][1] * this->m[3][2] + this->m[0][0] * this->m[1][3] * this->m[2][1] * this->m[3][2] +
		this->m[0][1] * this->m[1][0] * this->m[2][3] * this->m[3][2] - this->m[0][0] * this->m[1][1] * this->m[2][3] * this->m[3][2] -
		this->m[0][2] * this->m[1][1] * this->m[2][0] * this->m[3][3] + this->m[0][1] * this->m[1][2] * this->m[2][0] * this->m[3][3] +
		this->m[0][2] * this->m[1][0] * this->m[2][1] * this->m[3][3] - this->m[0][0] * this->m[1][2] * this->m[2][1] * this->m[3][3] -
		this->m[0][1] * this->m[1][0] * this->m[2][2] * this->m[3][3] + this->m[0][0] * this->m[1][1] * this->m[2][2] * this->m[3][3];

	return determinant;
}


Matrix4D Matrix4D::inverse() {

	float determinant = this->determinant();

	if (determinant != 0) {

		float invertDeterminant = 1.0f / determinant;

		Matrix4D tempMatrix = Matrix4D(

			this->m[1][2] * this->m[2][3] * this->m[3][1] - this->m[1][3] * this->m[2][2] * this->m[3][1] + this->m[1][3] * this->m[2][1] * this->m[3][2] - this->m[1][1] * this->m[2][3] * this->m[3][2] - this->m[1][2] * this->m[2][1] * this->m[3][3] + this->m[1][1] * this->m[2][2] * this->m[3][3],
			this->m[0][3] * this->m[2][2] * this->m[3][1] - this->m[0][2] * this->m[2][3] * this->m[3][1] - this->m[0][3] * this->m[2][1] * this->m[3][2] + this->m[0][1] * this->m[2][3] * this->m[3][2] + this->m[0][2] * this->m[2][1] * this->m[3][3] - this->m[0][1] * this->m[2][2] * this->m[3][3],
			this->m[0][2] * this->m[1][3] * this->m[3][1] - this->m[0][3] * this->m[1][2] * this->m[3][1] + this->m[0][3] * this->m[1][1] * this->m[3][2] - this->m[0][1] * this->m[1][3] * this->m[3][2] - this->m[0][2] * this->m[1][1] * this->m[3][3] + this->m[0][1] * this->m[1][2] * this->m[3][3],
			this->m[0][3] * this->m[1][2] * this->m[2][1] - this->m[0][2] * this->m[1][3] * this->m[2][1] - this->m[0][3] * this->m[1][1] * this->m[2][2] + this->m[0][1] * this->m[1][3] * this->m[2][2] + this->m[0][2] * this->m[1][1] * this->m[2][3] - this->m[0][1] * this->m[1][2] * this->m[2][3],
			this->m[1][3] * this->m[2][2] * this->m[3][0] - this->m[1][2] * this->m[2][3] * this->m[3][0] - this->m[1][3] * this->m[2][0] * this->m[3][2] + this->m[1][0] * this->m[2][3] * this->m[3][2] + this->m[1][2] * this->m[2][0] * this->m[3][3] - this->m[1][0] * this->m[2][2] * this->m[3][3],
			this->m[0][2] * this->m[2][3] * this->m[3][0] - this->m[0][3] * this->m[2][2] * this->m[3][0] + this->m[0][3] * this->m[2][0] * this->m[3][2] - this->m[0][0] * this->m[2][3] * this->m[3][2] - this->m[0][2] * this->m[2][0] * this->m[3][3] + this->m[0][0] * this->m[2][2] * this->m[3][3],
			this->m[0][3] * this->m[1][2] * this->m[3][0] - this->m[0][2] * this->m[1][3] * this->m[3][0] - this->m[0][3] * this->m[1][0] * this->m[3][2] + this->m[0][0] * this->m[1][3] * this->m[3][2] + this->m[0][2] * this->m[1][0] * this->m[3][3] - this->m[0][0] * this->m[1][2] * this->m[3][3],
			this->m[0][2] * this->m[1][3] * this->m[2][0] - this->m[0][3] * this->m[1][2] * this->m[2][0] + this->m[0][3] * this->m[1][0] * this->m[2][2] - this->m[0][0] * this->m[1][3] * this->m[2][2] - this->m[0][2] * this->m[1][0] * this->m[2][3] + this->m[0][0] * this->m[1][2] * this->m[2][3],
			this->m[1][1] * this->m[2][3] * this->m[3][0] - this->m[1][3] * this->m[2][1] * this->m[3][0] + this->m[1][3] * this->m[2][0] * this->m[3][1] - this->m[1][0] * this->m[2][3] * this->m[3][1] - this->m[1][1] * this->m[2][0] * this->m[3][3] + this->m[1][0] * this->m[2][1] * this->m[3][3],
			this->m[0][3] * this->m[2][1] * this->m[3][0] - this->m[0][1] * this->m[2][3] * this->m[3][0] - this->m[0][3] * this->m[2][0] * this->m[3][1] + this->m[0][0] * this->m[2][3] * this->m[3][1] + this->m[0][1] * this->m[2][0] * this->m[3][3] - this->m[0][0] * this->m[2][1] * this->m[3][3],
			this->m[0][1] * this->m[1][3] * this->m[3][0] - this->m[0][3] * this->m[1][1] * this->m[3][0] + this->m[0][3] * this->m[1][0] * this->m[3][1] - this->m[0][0] * this->m[1][3] * this->m[3][1] - this->m[0][1] * this->m[1][0] * this->m[3][3] + this->m[0][0] * this->m[1][1] * this->m[3][3],
			this->m[0][3] * this->m[1][1] * this->m[2][0] - this->m[0][1] * this->m[1][3] * this->m[2][0] - this->m[0][3] * this->m[1][0] * this->m[2][1] + this->m[0][0] * this->m[1][3] * this->m[2][1] + this->m[0][1] * this->m[1][0] * this->m[2][3] - this->m[0][0] * this->m[1][1] * this->m[2][3],
			this->m[1][2] * this->m[2][1] * this->m[3][0] - this->m[1][1] * this->m[2][2] * this->m[3][0] - this->m[1][2] * this->m[2][0] * this->m[3][1] + this->m[1][0] * this->m[2][2] * this->m[3][1] + this->m[1][1] * this->m[2][0] * this->m[3][2] - this->m[1][0] * this->m[2][1] * this->m[3][2],
			this->m[0][1] * this->m[2][2] * this->m[3][0] - this->m[0][2] * this->m[2][1] * this->m[3][0] + this->m[0][2] * this->m[2][0] * this->m[3][1] - this->m[0][0] * this->m[2][2] * this->m[3][1] - this->m[0][1] * this->m[2][0] * this->m[3][2] + this->m[0][0] * this->m[2][1] * this->m[3][2],
			this->m[0][2] * this->m[1][1] * this->m[3][0] - this->m[0][1] * this->m[1][2] * this->m[3][0] - this->m[0][2] * this->m[1][0] * this->m[3][1] + this->m[0][0] * this->m[1][2] * this->m[3][1] + this->m[0][1] * this->m[1][0] * this->m[3][2] - this->m[0][0] * this->m[1][1] * this->m[3][2],
			this->m[0][1] * this->m[1][2] * this->m[2][0] - this->m[0][2] * this->m[1][1] * this->m[2][0] + this->m[0][2] * this->m[1][0] * this->m[2][1] - this->m[0][0] * this->m[1][2] * this->m[2][1] - this->m[0][1] * this->m[1][0] * this->m[2][2] + this->m[0][0] * this->m[1][1] * this->m[2][2]
		);
		return invertDeterminant * tempMatrix;
	}

	exit(EXIT_FAILURE);
}

void Matrix4D::clean()
{
	double epsilon = pow(10, -5);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (this->m[i][j] < epsilon && this->m[i][j] > -epsilon)
				this->m[i][j] = 0.0f;
		}
	}
}



Matrix2D Matrix4D::toMat2()
{
	return Matrix2D(
		this->m[0][0], this->m[0][1],
		this->m[1][0], this->m[1][1]);
}

Matrix3D Matrix4D::toMat3()
{
	return Matrix3D(
		this->m[0][0], this->m[0][1], this->m[0][2], 
		this->m[1][0], this->m[1][1], this->m[1][2], 
		this->m[2][0], this->m[2][1], this->m[2][2]);
}

std::vector<float> Matrix4D::toColumnMatrix()
{
	std::vector<float> columnMajorMatrix(16);

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			columnMajorMatrix.at(j * 4 + i) = this->m[i][j];
		}
	}

	return columnMajorMatrix;
}

std::vector<float> Matrix4D::toMatrix16()
{
	std::vector<float> rowMajorMatrix(16);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rowMajorMatrix.at(i * 4 + j) = this->m[i][j];
		}
	}

	return rowMajorMatrix;
}

Matrix4D identity() {
	return Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}


Matrix4D translation(float x, float y, float z) {
	return Matrix4D(
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4D translation(Vector3D pos)
{
	return Matrix4D(
		1.0f, 0.0f, 0.0f, pos.x,
		0.0f, 1.0f, 0.0f, pos.y,
		0.0f, 0.0f, 1.0f, pos.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4D rotation(float angle, float x_axis, float y_axis, float z_axis)
{
	Vector3D v = Vector3D(x_axis, y_axis, z_axis).normalize();
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();

	if (angle < 0)
		angle += 360;
	float radAngle = angle * (float) DEGREES_TO_RADIANS;
	float sin_t = sin(radAngle);
	float cos_t = cos(radAngle);

	Matrix4D result = Matrix4D(
		x * x * (1 - cos_t) + cos_t, x * y * (1 - cos_t) - z * sin_t, x * z * (1 - cos_t) + y * sin_t, 0,
		x * y * (1 - cos_t) + z * sin_t, y * y * (1 - cos_t) + cos_t, y * z * (1 - cos_t) - x * sin_t, 0,
		x * z * (1 - cos_t) - y * sin_t, y * z * (1 - cos_t) + x * sin_t, z * z * (1 - cos_t) + cos_t, 0,
		0, 0, 0, 1);

	result.clean();

	return result;
}

Matrix4D rotation(float angle, Vector3D axis)
{
	Vector3D v = axis.normalize();
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();

	if (angle < 0)
		angle += 360;
	float radAngle = angle * (float)DEGREES_TO_RADIANS;
	float sin_t = sin(radAngle);
	float cos_t = cos(radAngle);

	Matrix4D result = Matrix4D(
		x * x * (1 - cos_t) + cos_t, x * y * (1 - cos_t) - z * sin_t, x * z * (1 - cos_t) + y * sin_t, 0,
		x * y * (1 - cos_t) + z * sin_t, y * y * (1 - cos_t) + cos_t, y * z * (1 - cos_t) - x * sin_t, 0,
		x * z * (1 - cos_t) - y * sin_t, y * z * (1 - cos_t) + x * sin_t, z * z * (1 - cos_t) + cos_t, 0,
		0, 0, 0, 1);

	result.clean();

	return result;
}

Matrix4D rotation(Quaternion q)
{
	return qGLMatrix(q);
}

Matrix4D scale(float x, float y, float z) {
	return Matrix4D(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4D lookAt(Vector3D eye, Vector3D center, Vector3D up) { // Column Major Already
	Vector3D zAxis = eye - center;
	zAxis = zAxis.normalize();
	Vector3D xAxis = up.crossProduct(zAxis);
	xAxis = xAxis.normalize();
	Vector3D yAxis = zAxis.crossProduct(xAxis);

	return Matrix4D(
		xAxis.getX(), yAxis.getX(), zAxis.getX(), 0,
		xAxis.getY(), yAxis.getY(), zAxis.getY(), 0,
		xAxis.getZ(), yAxis.getZ(), zAxis.getZ(), 0,
		-xAxis.dotProduct(eye), -yAxis.dotProduct(eye), -zAxis.dotProduct(eye), 1
		);
}

Matrix4D orthographicMatrix(float left, float right, float bottom, float top, float nearr, float farr) {
	return Matrix4D(
		(2 / (right - left)), 0, 0, ((left + right) / (left - right)),
		0, (2 / (top - bottom)), 0, ((bottom + top) / (bottom - top)),
		0, 0, (-2 / (farr - nearr)), ((nearr + farr) / (nearr - farr)),
		0, 0, 0, 1);
}

Matrix4D perspectiveMatrix(float fovy, float aspect, float nearZ, float farZ) {
	float theta = fovy * 0.5f * (float)DEGREES_TO_RADIANS;
	float d = 1 / tan(theta);
	return Matrix4D(
		(d / aspect), 0, 0, 0,
		0, d, 0, 0,
		0, 0, ((nearZ + farZ) / (nearZ - farZ)), ((2 * farZ*nearZ) / (nearZ - farZ)),
		0, 0, -1, 0);
}
