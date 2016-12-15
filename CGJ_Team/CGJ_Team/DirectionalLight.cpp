#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3D direction, Vector3D color, GLuint ubo_bp)
{
	lightDirection = direction;
	lightColor = color;

	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 6, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, ubo_bp, bufferId);

	float dir[3] = { direction.x, direction.y, direction.z };
	float col[3] = { color.x, color.y, color.z };

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 3, dir);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 3, sizeof(float) * 3, col);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

DirectionalLight::~DirectionalLight()
{
}
