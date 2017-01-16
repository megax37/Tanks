#ifndef _PARTICLE_SCENE_NODE_
#define _PARTICLE_SCENE_NODE_

#include "SceneNode.h"

class ParticleSceneNode : public SceneNode
{
public:

	ParticleSceneNode();
	~ParticleSceneNode();

	virtual void draw(Matrix4D parentTransform) override;

	void setParticleCount(int particleCount);
	void setParticlesTransforms(std::vector<Matrix4D> transforms);
	void setParticlesLifes(std::vector<float> lifes);

	ParticleSceneNode* copyNode();

private:

	int numParticles;

	std::vector<Matrix4D> particlesTransforms;
	std::vector<float> particlesLifes;
};

#endif