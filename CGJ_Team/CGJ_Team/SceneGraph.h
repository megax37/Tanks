#ifndef _SCENE_GRAPH_
#define _SCENE_GRAPH_

#include "SceneNode.h"

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

	SceneNode* getRoot();
	SceneNode* createNode();
	Camera* getCamera();
	void setCamera(Camera* cam);
	void setLight(DirectionalLight* light);

	void draw();

	void destroy();

private:
	SceneNode* root;
	Camera* camera;
	DirectionalLight* directionalLight;

};

#endif