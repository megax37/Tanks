#include "Explosion.h"

Explosion::Explosion(ParticleSceneNode * particleNode, int particleCount) : ParticleSystem(particleNode, particleCount)
{
}

Explosion::~Explosion()
{
}

void Explosion::initParticles(Vector3D startPos)
{
	float v, theta, phi;
	int i;

	for (i = 0; i < numParticles; i++)
	{
		v = 0.03f * frand() + 0.01f;
		phi = frand() * (float)PI;
		theta = 2.0f * frand() * (float)PI;

		particles[i].x = startPos.x;
		particles[i].y = startPos.y;
		particles[i].z = startPos.z;
		particles[i].vx = v * cos(theta) * sin(phi);
		particles[i].vy = v * cos(phi);
		particles[i].vz = v * sin(theta) * sin(phi);
		particles[i].ax = 0.0f; /* simular um pouco de vento */
		particles[i].ay = -0.001f; /* simular a aceleração da gravidade */
		particles[i].az = 0.0f;

		particles[i].life = 1.0f;		/* vida inicial */
		particles[i].fade = 0.02f;	    /* step de decréscimo da vida para cada iteração */
	}

	this->alive = true;
	this->particleSceneNode->setVisible(true);
}
