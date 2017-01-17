#include "ParticleSceneNode.h"

ParticleSceneNode::ParticleSceneNode() : SceneNode()
{
}

ParticleSceneNode::~ParticleSceneNode()
{
}

void ParticleSceneNode::draw(Matrix4D parentTransform)
{
	shaderProgram->BeginShader();

	if (visible && meshObj) {
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}

	shaderProgram->EndShader();
}

void ParticleSceneNode::setParticleCount(int particleCount)
{
	numParticles = particleCount;
}

void ParticleSceneNode::setParticlesTransforms(std::vector<Matrix4D> transforms)
{
	particlesTransforms = transforms;
}

void ParticleSceneNode::setParticlesLifes(std::vector<float> lifes)
{
	particlesLifes = lifes;
}

ParticleSceneNode * ParticleSceneNode::copyNode()
{
	ParticleSceneNode* copy = new ParticleSceneNode();
	copy->setMesh(this->meshObj);
	copy->setMaterial(this->material);
	copy->setShaderProgram(this->shaderProgram);
	copy->setTexture(this->texture);
	copy->setMatrix(this->modelMatrix);
	copy->setScale(this->scaleMatrix);
	return copy;
}
