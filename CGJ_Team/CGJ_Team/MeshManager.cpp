#include "MeshManager.h"

MeshManager* MeshManager::m_instance;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

MeshManager * MeshManager::instance()
{
	if (!m_instance) {
		m_instance = new MeshManager();
	}
	return m_instance;
}

void MeshManager::add(const std::string& name, Mesh * mesh)
{
	// Store in map
	meshes.insert(std::pair<std::string, Mesh*>(name, mesh));
}

Mesh * MeshManager::get(const std::string& name)
{
	return meshes.find(name)->second;
}

void MeshManager::destroy()
{
	meshes.clear();
}
