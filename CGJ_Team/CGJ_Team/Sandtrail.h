#ifndef _SANDTRAIL_
#define _SANDTRAIL_

#include "ParticleSystem.h"

class Sandtrail : public ParticleSystem
{
public:

	Sandtrail(ParticleSceneNode * particleNode, int particleCount);
	~Sandtrail();

	void initParticles(Vector3D startPos);

private:

};

#endif