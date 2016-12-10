#ifndef _MATERIAL_MANAGER_
#define _MATERIAL_MANAGER_

#include "Material.h"

class MaterialManager {

public:
	static MaterialManager* instance();
	void add(const std::string& name, Material* mesh);
	Material* get(const std::string& name);

	void destroy();

private:
	static MaterialManager* m_instance;

	std::map<std::string, Material*> materials;

	MaterialManager();
	~MaterialManager();
};

#endif