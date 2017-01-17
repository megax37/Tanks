#include "Sandtrail.h"

Sandtrail::Sandtrail(ParticleSceneNode * particleNode, int particleCount) : ParticleSystem(particleNode, particleCount)
{
}

Sandtrail::~Sandtrail()
{
}

void Sandtrail::initParticles(Vector3D startPos)
{
	float v, theta, phi;
	int i;

	for (i = 0; i < numParticles; i++)
	{
		v = 0.003f * frand() + 0.001f;
		phi = frand() * (float)PI;
		theta = 2.0f * frand() * (float)PI;

		//particles[i].vx = v * cos(theta) * sin(phi);
		particles[i].vx = v * cos(phi);
		particles[i].vy = v * sin(phi) * 3;
		particles[i].vz = v * cos(phi);
		particles[i].x = startPos.x + particles[i].vx * 2;
		particles[i].y = startPos.y + particles[i].vy * 2;
		particles[i].z = startPos.z + particles[i].vz * 2;
		particles[i].ax = 0.0f; /* simular um pouco de vento */
		particles[i].ay = -0.0001f; /* simular a aceleração da gravidade */
		particles[i].az = 0.0f;

		particles[i].life = 1.0f;		/* vida inicial */
		particles[i].fade = 0.02f * frand() + 0.02f;	/* step de decréscimo da vida para cada iteração */
	}

	this->alive = true;
	this->particleSceneNode->setVisible(true);
}
