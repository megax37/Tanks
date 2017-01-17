#ifndef _EXPLOSION_
#define _EXPLOSION_

#include "ParticleSystem.h"

class Explosion : public ParticleSystem
{
public:

	Explosion(ParticleSceneNode * particleNode, int particleCount);
	~Explosion();

	void initParticles(Vector3D startPos);

private:

};

#endif