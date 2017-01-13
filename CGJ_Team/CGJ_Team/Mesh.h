#ifndef _MESH_
#define _MESH_

class ShaderProgram;

#include "engine.h"

/// Types of Vertex Attributes
enum AttribType {
	VERTICES,
	TEXCOORDS,
	NORMALS,
	TANGENT,
	BITANGENT
};

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;


class Mesh {

private:

	GLuint VaoId;
	bool TexcoordsLoaded, NormalsLoaded;

	std::vector <Vertex> Vertices, vertexData;
	std::vector <Texcoord> Texcoords, texcoordData;
	std::vector <Normal> Normals, normalData;

	std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;

	void parseVertex(std::stringstream& sin);
	void parseTexcoord(std::stringstream& sin);
	void parseNormal(std::stringstream& sin);
	void parseFace(std::stringstream& sin);
	void parseLine(std::stringstream& sin);

	void loadMeshData(const std::string& filename);
	void processMeshData();
	void freeMeshData();
	void createBufferObject();

public:

	Mesh(const std::string& filename);
	~Mesh();

	void create();
	void draw(ShaderProgram* shader, Matrix4D transform);
};

#endif