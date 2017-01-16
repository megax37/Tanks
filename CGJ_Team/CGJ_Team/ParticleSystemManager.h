#ifndef _PARTICLE_SYSTEM_MANAGER_
#define _PARTICLE_SYSTEM_MANAGER_

#include "ParticleSystem.h"

class ParticleSystemManager {

public:
	static ParticleSystemManager* instance();
	void add(const std::string& name, ParticleSystem* system);
	ParticleSystem* get(const std::string& name);

	void destroy();

	void update(int elapsedTime);
	void move();

private:
	static ParticleSystemManager* m_instance;

	std::multimap<std::string, ParticleSystem*> particle_systems;

	ParticleSystemManager();
	~ParticleSystemManager();
};

#endif