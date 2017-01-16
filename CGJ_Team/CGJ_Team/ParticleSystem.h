#ifndef _PARTICLE_SYSTEM_
#define _PARTICLE_SYSTEM_

#include "Object.h"
#include "ParticleSceneNode.h"

#define frand()	((float)rand()/RAND_MAX)

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

	virtual void initParticles(Vector3D startPos) = 0;

	void update(int elapsedTime);
	void move();
	void reset();

	bool isAlive();

protected:

	bool alive;
	int numParticles;
	std::vector<Particle> particles;
	ParticleSceneNode* particleSceneNode;

	std::vector<Matrix4D> particlesTransforms;
	std::vector<float> particlesLifes;
};

#endif

