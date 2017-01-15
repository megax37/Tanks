#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ParticleSceneNode * particleNode, int particleCount)
{
	particleSceneNode = particleNode;
	numParticles = particleCount;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(int elapsedTime)
{
	float h = 0.125f * elapsedTime;
	for (int i = 0; i < numParticles; i++)
	{
		particles[i].x += (h*particles[i].vx);
		particles[i].y += (h*particles[i].vy);
		particles[i].z += (h*particles[i].vz);
		particles[i].vx += (h*particles[i].ax);
		particles[i].vy += (h*particles[i].ay);
		particles[i].vz += (h*particles[i].az);
		particles[i].life -= particles[i].fade;
	}
}

void ParticleSystem::move()
{
	for (int i = 0; i < numParticles; i++)
	{
		particlesTransforms[i] = translation(particles[i].x, particles[i].y, particles[i].z);
		particlesLifes[i] = particles[i].life;
	}

	particleSceneNode->setParticlesTransforms(particlesTransforms);
	particleSceneNode->setParticlesLifes(particlesLifes);
}
