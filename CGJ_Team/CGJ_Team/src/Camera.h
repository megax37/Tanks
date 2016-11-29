#ifndef _CAMERA_
#define _CAMERA_

#include "engine.h"

class Camera
{
public:

	Camera(GLint puId, GLint vuId);
	~Camera();

	void setViewMatrix(Matrix4D view);
	void setProjectionMatrix(Matrix4D projection);
	void setAltProjectionMatrix(Matrix4D projection);
	void changeProjectionMode();

	void loadMatrices();

private:
	GLint ViewMatrix_UId, ProjectionMatrix_UId;

	Matrix4D projectionMatrix;
	Matrix4D secondaryProjectionMatrix;
	Matrix4D viewMatrix;
};

#endif