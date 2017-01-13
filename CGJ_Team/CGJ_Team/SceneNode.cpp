#include "SceneNode.h"

SceneNode::SceneNode()
{
	modelMatrix = identity();
	scaleMatrix = modelMatrix;
	visible = true;
}

SceneNode::~SceneNode()
{
	
}

void SceneNode::setParent(SceneNode * parent)
{
	parentNode = parent;
}

void SceneNode::setMesh(Mesh * mesh)
{
	meshObj = mesh;
}

void SceneNode::setTexture(Texture * tex)
{
	texture = tex;
}

void SceneNode::setMaterial(Material * mat)
{
	material = mat;
}

void SceneNode::setMatrix(Matrix4D transform)
{
	modelMatrix = transform;
}

void SceneNode::setScale(Matrix4D scale)
{
	scaleMatrix = scale;
}

void SceneNode::setShaderProgram(ShaderProgram * shader)
{
	shaderProgram = shader;
}

void SceneNode::setVisible(bool flag)
{
	visible = flag;
}

bool SceneNode::isVisible()
{
	return visible;
}

SceneNode * SceneNode::createNode()
{
	SceneNode* child = new SceneNode();
	child->setParent(this);
	child->setShaderProgram(shaderProgram);
	childrenNodes.push_back(child);
	return child;
}

void SceneNode::applyLTransform(Matrix4D transform)
{
	modelMatrix = transform * modelMatrix;
}

void SceneNode::applyRTransform(Matrix4D transform)
{
	modelMatrix = modelMatrix * transform;
}

void SceneNode::draw(Matrix4D parentTransform)
{
	shaderProgram->BeginShader();

	Matrix4D finalMatrix = parentTransform * modelMatrix;
	if (visible && meshObj) {

		if (material) {
			material->loadToShader(shaderProgram); // Load Material
			GLint NormalMatrix_UId = shaderProgram->getUniform("NormalMatrix");
			Matrix3D normalMatrix = finalMatrix.toMat3().inverse().transpose();
			glUniformMatrix3fv(NormalMatrix_UId, 1, GL_FALSE, &normalMatrix.toColumnMatrix()[0]);
		}

		if (texture) {
			texture->loadToShader(shaderProgram); // Load Texture
			meshObj->draw(shaderProgram, finalMatrix * scaleMatrix); // Draw Mesh
			texture->unloadFromShader(shaderProgram); // Unload Texture
		}
		else {
			meshObj->draw(shaderProgram, finalMatrix * scaleMatrix); // Draw Mesh
		}
	}

	for (auto it = childrenNodes.begin(); it < childrenNodes.end(); ++it)
	{
		(*it)->draw(finalMatrix);
	}

	shaderProgram->EndShader();
}

void SceneNode::destroy()
{
	for (auto it = childrenNodes.begin(); it < childrenNodes.end(); ++it)
	{
		(*it)->destroy();
	}
	childrenNodes.clear();
	meshObj = nullptr;
	shaderProgram = nullptr;
	parentNode = nullptr;
}

/*Matrix4D SceneNode::getFinalTransform()
{
	if (parentNode != nullptr) {
		return parentNode->getFinalTransform() * modelMatrix;
	}
	return modelMatrix;
}*/
