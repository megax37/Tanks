#ifndef _SHADER_PROGRAM_
#define _SHADER_PROGRAM_

#include "engine.h"

class ShaderProgram {

public:

	ShaderProgram();
	~ShaderProgram();

	void addShader(const GLenum shader_type, const std::string& filename);
	void create();
	//Faz o link dos atributos
	void addAttribute(const std::string& pName, int index);
	void addUniform(const std::string& uName);
	void addUniformBlock(const std::string& bName, int location);

	GLint getUniform(const std::string& uName);

	//Inicia o shader
	void BeginShader();
	//Termina o shader
	void EndShader();

	void destroy();

private:
	GLuint VertexShaderId, FragmentShaderId, ProgramId;

	std::map<std::string, GLint> uniforms;

	const std::string read(const std::string& filename);
	const GLuint checkCompilation(const GLuint shader_id, const std::string& filename);
	void checkLinkage(const GLuint program_id);
};

#endif