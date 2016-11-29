#include "Camera.h"

Camera::Camera(GLint puId, GLint vuId)
{
	ProjectionMatrix_UId = puId;
	ViewMatrix_UId = vuId;
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
	glUniformMatrix4fv(ViewMatrix_UId, 1, GL_FALSE, &viewMatrix.toColumnMatrix()[0]);
	glUniformMatrix4fv(ProjectionMatrix_UId, 1, GL_FALSE, &projectionMatrix.toColumnMatrix()[0]);
}
