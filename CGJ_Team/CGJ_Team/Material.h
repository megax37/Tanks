#ifndef _MATERIAL_
#define _MATERIAL_

#include "engine.h"

class Material
{
public:
	Material(const std::string& filename);
	~Material();

	std::string MaterialName();
	Vector3D Ka();
	Vector3D Kd();
	Vector3D Ks();
	Vector3D Ke();
	float Ns();

private:
	std::string materialName;

	Vector3D ambientReflectivity;
	Vector3D diffuseReflectivity;
	Vector3D specularReflectivity;
	Vector3D emissiveReflectivity;

	float specularExponent;

	void loadMaterialData(const std::string& filename);
	void parseLine(std::stringstream& sin);
	void parseName(std::stringstream& sin);
	void parseExponent(std::stringstream& sin);
	void parseAmbient(std::stringstream& sin);
	void parseDiffuse(std::stringstream& sin);
	void parseSpecular(std::stringstream& sin);
	void parseEmissive(std::stringstream& sin);
};

#endif