#include "MaterialManager.h"

MaterialManager* MaterialManager::m_instance;

MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
}

MaterialManager * MaterialManager::instance()
{
	if (!m_instance) {
		m_instance = new MaterialManager();
	}
	return m_instance;
}

void MaterialManager::add(const std::string& name, Material * mesh)
{
	// Store in map
	materials.insert(std::pair<std::string, Material*>(name, mesh));
}

Material * MaterialManager::get(const std::string& name)
{
	return materials.find(name)->second;
}

void MaterialManager::destroy()
{
	materials.clear();
}
