#ifndef _SCENE_NODE_
#define _SCENE_NODE_

#include "engine.h"
#include "ShaderProgramManager.h"

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

	void setShaderProgram(ShaderProgram* shader);

	void setVisible(bool flag);
	bool isVisible();
	void setUI();

	SceneNode* createNode();
	SceneNode* copyNode();
	void addNode(SceneNode* child);
	void applyLTransform(Matrix4D transform);
	void applyRTransform(Matrix4D transform);

	virtual void draw(Matrix4D parentTransform);

	void destroy();

protected:
	SceneNode* parentNode;
	std::vector<SceneNode*> childrenNodes;

	Mesh* meshObj;
	Material* material;
	Texture* texture;

	Matrix4D modelMatrix;
	Matrix4D scaleMatrix;

	ShaderProgram* shaderProgram;
	ShaderProgram* silhouetteShader;

	bool isUI;
	bool visible;

	//Matrix4D getFinalTransform();
};

#endif