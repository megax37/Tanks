#ifndef _SCENE_NODE_
#define _SCENE_NODE_

#include "engine.h"

class SceneNode
{
public:
	SceneNode();
	~SceneNode();

	void setParent(SceneNode* parent);
	void setMesh(Mesh* mesh);
	void setTexture(Texture* tex);
	void setMaterial(Material* mat);
	void setMatrix(Matrix4D transform);
	//For independent scaling, if a scaling node propagation is desired, insert it into modelMatrix transform
	void setScale(Matrix4D scale);
	void setColor(Vector4D matColor);
	void setShaderProgram(ShaderProgram* shader);

	SceneNode* createNode();
	void applyLTransform(Matrix4D transform);
	void applyRTransform(Matrix4D transform);

	void draw(Matrix4D parentTransform);

	void destroy();

private:
	SceneNode* parentNode;
	std::vector<SceneNode*> childrenNodes;

	Mesh* meshObj;
	Material* material;
	Texture* texture;
	Matrix4D modelMatrix;
	Matrix4D scaleMatrix;
	Vector4D color;
	ShaderProgram* shaderProgram;

	void removeChildNode(SceneNode * node);


	//Matrix4D getFinalTransform();
};

#endif