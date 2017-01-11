#include "SceneNode.h"

SceneNode::SceneNode()
{
	modelMatrix = identity();
	scaleMatrix = modelMatrix;
	color = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);
	visible = true;
}

SceneNode::~SceneNode()
{
	//if(parentNode != NULL) parentNode->removeChildNode(this);
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

void SceneNode::setColor(Vector4D matColor)
{
	color = matColor;
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

void SceneNode::removeChildNode(SceneNode * node) {

	/*for (int i = 0; i < childrenNodes.size(); i++)
	{
		if(childrenNodes[i] == node)
		{
			childrenNodes.erase(childrenNodes.begin() + i);
			break;
		}
	}*/
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
		//glBindVertexArray(meshObj->getVaoId());

		if (material) {
			GLint Diffuse_UId = shaderProgram->getUniform("DiffuseReflectivity");
			Vector3D diffuse = material->Kd();
			glUniform3f(Diffuse_UId, diffuse.x, diffuse.y, diffuse.z);

			GLint Specular_UId = shaderProgram->getUniform("SpecularReflectivity");
			Vector3D specular = material->Ks();
			glUniform3f(Specular_UId, specular.x, specular.y, specular.z);

			GLint Exponent_UId = shaderProgram->getUniform("SpecularExponent");
			glUniform1f(Exponent_UId, material->Ns());

			GLint NormalMatrix_UId = shaderProgram->getUniform("NormalMatrix");
			Matrix3D normalMatrix = finalMatrix.toMat3().inverse().transpose();
			glUniformMatrix3fv(NormalMatrix_UId, 1, GL_FALSE, &normalMatrix.toColumnMatrix()[0]);
		}
		else {
			GLint Color_UId = shaderProgram->getUniform("Color");
			glUniform4f(Color_UId, color.x, color.y, color.z, color.w);
		}

		GLint TexMode_UId = shaderProgram->getUniform("TexMode");
		if (texture) {
			glActiveTexture(GL_TEXTURE0);
			texture->bind();
			glUniform1i(TexMode_UId, 1);
			GLint Tex_UId = shaderProgram->getUniform("Texmap");
			glUniform1i(Tex_UId, 0);
		}

		meshObj->draw(shaderProgram, finalMatrix * scaleMatrix);

/** /
		GLint ModelMatrix_UId = shaderProgram->getUniform("ModelMatrix");
		glUniformMatrix4fv(ModelMatrix_UId, 1, GL_FALSE, &(finalMatrix * scaleMatrix).toColumnMatrix()[0]);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)meshObj->vertices().size());
/**/
		if (texture) {
			texture->unbind();
			glUniform1i(TexMode_UId, 0);
		}
		glBindVertexArray(0);
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
