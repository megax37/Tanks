#ifndef _MESH_MANAGER_
#define _MESH_MANAGER_

#include "Mesh.h"

class MeshManager {

public:
	static MeshManager* instance();
	void add(const std::string& name, Mesh* mesh);
	Mesh* get(const std::string& name);

	void destroy();

private:
	static MeshManager* m_instance;

	std::map<std::string, Mesh*> meshes;

	MeshManager();
	~MeshManager();
};

#endif