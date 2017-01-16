#include "ParticleSystemManager.h"

ParticleSystemManager* ParticleSystemManager::m_instance;

ParticleSystemManager::ParticleSystemManager()
{
}

ParticleSystemManager::~ParticleSystemManager()
{
}

ParticleSystemManager * ParticleSystemManager::instance()
{
	if (!m_instance) {
		m_instance = new ParticleSystemManager();
	}
	return m_instance;
}

void ParticleSystemManager::add(const std::string& name, ParticleSystem * system)
{
	// Store in map
	particle_systems.insert(std::pair<std::string, ParticleSystem*>(name, system));
}

ParticleSystem * ParticleSystemManager::get(const std::string& name)
{
	for (auto it = particle_systems.begin(); it != particle_systems.end(); ++it) {
		if (it->first == name && !it->second->isAlive()) return it->second;
	}
	return nullptr;
}

void ParticleSystemManager::destroy()
{
	particle_systems.clear();
}

void ParticleSystemManager::update(int elapsedTime)
{
	for (auto it = particle_systems.begin(); it != particle_systems.end(); ++it) {
		it->second->update(elapsedTime);
	}
}

void ParticleSystemManager::move()
{
	for (auto it = particle_systems.begin(); it != particle_systems.end(); ++it) {
		it->second->move();
	}
}
