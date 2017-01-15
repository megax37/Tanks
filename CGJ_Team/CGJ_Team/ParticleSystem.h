#ifndef _PARTICLE_SYSTEM_
#define _PARTICLE_SYSTEM_

#include "Object.h"
#include "ParticleSceneNode.h"

typedef struct {
	float life;		  // lifespan
	float fade;		  // fade
	float x, y, z;    // position
	float vx, vy, vz; // velocity 
	float ax, ay, az; // aceleration
} Particle;

class ParticleSystem : public Object
{
public:

	ParticleSystem(ParticleSceneNode * particleNode, int particleCount);
	~ParticleSystem();

	virtual void initParticles() = 0;

	void update(int elapsedTime);
	void move();

protected:

	int numParticles;
	std::vector<Particle> particles;
	ParticleSceneNode* particleSceneNode;

	std::vector<Matrix4D> particlesTransforms;
	std::vector<float> particlesLifes;
};

#endif

