#include "SceneGraphManager.h"

SceneGraphManager* SceneGraphManager::m_instance;

SceneGraphManager::SceneGraphManager()
{
}

SceneGraphManager::~SceneGraphManager()
{
}

SceneGraphManager * SceneGraphManager::instance()
{
	if (!m_instance) {
		m_instance = new SceneGraphManager();
	}
	return m_instance;
}

void SceneGraphManager::add(const std::string & name, SceneGraph * shader)
{
	// Store in map
	scenes.insert(std::pair<std::string, SceneGraph*>(name, shader));
}

SceneGraph * SceneGraphManager::get(const std::string & name)
{
	return scenes.find(name)->second;
}

void SceneGraphManager::destroy()
{
	for (auto it = scenes.begin(); it != scenes.end(); ++it)
	{
		it->second->destroy();
	}
	scenes.clear();
}
