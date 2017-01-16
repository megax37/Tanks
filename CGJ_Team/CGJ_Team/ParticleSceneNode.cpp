#include "ParticleSceneNode.h"

ParticleSceneNode::ParticleSceneNode(int particleCount) : SceneNode()
{
	numParticles = particleCount;
}

ParticleSceneNode::~ParticleSceneNode()
{
}

void ParticleSceneNode::draw(Matrix4D parentTransform)
{
	shaderProgram->BeginShader();

	if (visible && meshObj) {
		if (texture) {
			texture->loadToShader(shaderProgram); // Load Texture

			GLint Life_UId = shaderProgram->getUniform("Life");
			for (int i = 0; i < numParticles; i++)
			{
				if (particlesLifes[i] > 0.0f) {
					glUniform1f(Life_UId, particlesLifes[i]);
					meshObj->draw(shaderProgram, particlesTransforms[i] * scaleMatrix); // Draw Mesh
				}
			}

			texture->unloadFromShader(shaderProgram); // Unload Texture
		}
	}

	shaderProgram->EndShader();
}

void ParticleSceneNode::setParticlesTransforms(std::vector<Matrix4D> transforms)
{
	particlesTransforms = transforms;
}

void ParticleSceneNode::setParticlesLifes(std::vector<float> lifes)
{
	particlesLifes = lifes;
}
