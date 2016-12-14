#include "Camera.h"

Camera::Camera(GLuint ubo_bp)
{
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 32, 0, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, ubo_bp, bufferId);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Camera::~Camera()
{
}

void Camera::setProjectionMatrix(Matrix4D projection)
{
	projectionMatrix = projection;
}

void Camera::setAltProjectionMatrix(Matrix4D projection)
{
	secondaryProjectionMatrix = projection;
}

void Camera::changeProjectionMode()
{
	Matrix4D aux = projectionMatrix;
	projectionMatrix = secondaryProjectionMatrix;
	secondaryProjectionMatrix = aux;
}

void Camera::setViewMatrix(Matrix4D view)
{
	viewMatrix = view;
}

void Camera::loadMatrices()
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, &viewMatrix.toColumnMatrix()[0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, &projectionMatrix.toColumnMatrix()[0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
