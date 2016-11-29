#include "SceneNode.h"

SceneNode::SceneNode()
{
	modelMatrix = identity();
	scaleMatrix = modelMatrix;
	color = Vector4D(0.0f, 0.0f, 0.0f, -1.0f);
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

void SceneNode::setMatrix(Matrix4D transform)
{
	modelMatrix = transform;
}

void SceneNode::setScale(Matrix4D scale)
{
	scaleMatrix = scale;
}

void SceneNode::setColor(Vector4D matColor)
{
	color = matColor;
}

void SceneNode::setShaderProgram(ShaderProgram * shader)
{
	shaderProgram = shader;
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
	Matrix4D finalMatrix = parentTransform * modelMatrix;
	if (meshObj) {
		glBindVertexArray(meshObj->getVaoId());
		GLint Color_UId = shaderProgram->getUniform("Color");
		glUniform4f(Color_UId, color.x, color.y, color.z, color.w);
		GLint ModelMatrix_UId = shaderProgram->getUniform("ModelMatrix");
		glUniformMatrix4fv(ModelMatrix_UId, 1, GL_FALSE, &(finalMatrix * scaleMatrix).toColumnMatrix()[0]);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)meshObj->vertices().size());
	}

	for (auto it = childrenNodes.begin(); it < childrenNodes.end(); ++it)
	{
		(*it)->draw(finalMatrix);
	}
	glBindVertexArray(0);
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
