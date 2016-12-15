#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include "engine.h"

class DirectionalLight
{
public:

	DirectionalLight(Vector3D direction, Vector3D color, GLuint ubo_bp);
	~DirectionalLight();

private:

	Vector3D lightDirection;
	Vector3D lightColor;

	GLuint bufferId;
};

#endif