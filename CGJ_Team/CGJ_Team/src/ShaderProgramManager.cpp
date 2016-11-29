#include "ShaderProgramManager.h"

ShaderProgramManager* ShaderProgramManager::m_instance;

ShaderProgramManager::ShaderProgramManager()
{
}

ShaderProgramManager::~ShaderProgramManager()
{
}

ShaderProgramManager * ShaderProgramManager::instance()
{
	if (!m_instance) {
		m_instance = new ShaderProgramManager();
	}
	return m_instance;
}

void ShaderProgramManager::add(const std::string& name, ShaderProgram * shader)
{
	// Store in map
	shaders.insert(std::pair<std::string, ShaderProgram*>(name, shader));
}

ShaderProgram * ShaderProgramManager::get(const std::string& name)
{
	return shaders.find(name)->second;
}

void ShaderProgramManager::destroy()
{
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		it->second->destroy();
	}
	shaders.clear();
}
