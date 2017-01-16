#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ParticleSceneNode * particleNode, int particleCount)
{
	particleSceneNode = particleNode;
	particleSceneNode->setVisible(false);
	numParticles = particleCount;
	particleSceneNode->setParticleCount(numParticles);
	alive = false;

	particles.reserve(numParticles);
	particlesTransforms.reserve(numParticles);
	particlesLifes.reserve(numParticles);

	Particle p;
	p.x = 0.0f;
	p.y = 0.0f;
	p.z = 0.0f;
	p.vx = 0.0f;
	p.vy = 0.0f;
	p.vz = 0.0f;
	p.ax = 0.0f;
	p.ay = 0.0f;
	p.az = 0.0f;
	p.life = 0.0f;
	p.fade = 0.0f;

	Matrix4D m = identity();

	for (int i = 0; i < numParticles; i++)
	{
		particles.push_back(p);
		particlesTransforms.push_back(m);
		particlesLifes.push_back(0.0f);
	}
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(int elapsedTime)
{
	if (alive) {
		bool isAlive = false;
		float h = 0.125f * elapsedTime;

		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].life != 0.0f) {
				particles[i].x += (h*particles[i].vx);
				particles[i].y += (h*particles[i].vy);
				particles[i].z += (h*particles[i].vz);
				particles[i].vx += (h*particles[i].ax);
				particles[i].vy += (h*particles[i].ay);
				particles[i].vz += (h*particles[i].az);
				particles[i].life -= particles[i].fade;

				if (particles[i].life < 0.0f) particles[i].life = 0.0f;
				else if (particles[i].life > 0.0f) isAlive = true;
			}
		}

		if (!isAlive) alive = false, particleSceneNode->setVisible(false);
	}
}

void ParticleSystem::move()
{
	if (alive) {
		for (int i = 0; i < numParticles; i++)
		{
			particlesTransforms[i] = translation(particles[i].x, particles[i].y, particles[i].z);
			particlesLifes[i] = particles[i].life;
		}

		particleSceneNode->setParticlesTransforms(particlesTransforms);
		particleSceneNode->setParticlesLifes(particlesLifes);
	}
}

void ParticleSystem::reset()
{
	particleSceneNode->setVisible(false);
	alive = false;

	Matrix4D m = identity();

	for (int i = 0; i < numParticles; i++)
	{
		particles[i].x = 0.0f;
		particles[i].y = 0.0f;
		particles[i].z = 0.0f;
		particles[i].vx = 0.0f;
		particles[i].vy = 0.0f;
		particles[i].vz = 0.0f;
		particles[i].ax = 0.0f;
		particles[i].ay = 0.0f;
		particles[i].az = 0.0f;
		particles[i].life = 0.0f;
		particles[i].fade = 0.0f;

		particlesTransforms[i] = m;
		particlesLifes[i] = 0.0f;
	}
}

bool ParticleSystem::isAlive()
{
	return alive;
}
