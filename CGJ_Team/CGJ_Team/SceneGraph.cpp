#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	root = new SceneNode();
}

SceneGraph::~SceneGraph()
{
}

SceneNode * SceneGraph::getRoot()
{
	return root;
}

SceneNode * SceneGraph::createNode()
{
	return root->createNode();
}

Camera * SceneGraph::getCamera()
{
	return camera;
}

void SceneGraph::setCamera(Camera * cam)
{
	camera = cam;
}

void SceneGraph::setLight(DirectionalLight * light)
{
	directionalLight = light;
}

void SceneGraph::draw()
{
	camera->loadMatrices();
	root->draw(identity());
}

void SceneGraph::destroy()
{
	root->destroy();
	delete root;
	delete camera;
}
