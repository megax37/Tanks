#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	ProgramId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::addShader(const GLenum shader_type, const std::string & filename)
{
	const GLuint shader_id = glCreateShader(shader_type);
	const std::string scode = read(filename);
	const GLchar* code = scode.c_str();
	glShaderSource(shader_id, 1, &code, 0);
	glCompileShader(shader_id);
	checkCompilation(shader_id, filename);
	glAttachShader(ProgramId, shader_id);

	if (shader_type == GL_VERTEX_SHADER)
		VertexShaderId = shader_id;
	else if (shader_type == GL_FRAGMENT_SHADER)
		FragmentShaderId = shader_id;
}

void ShaderProgram::create()
{
	glLinkProgram(ProgramId);
	checkLinkage(ProgramId);

	checkOpenGLError("ERROR: Could not create shaders.");
}

void ShaderProgram::addAttribute(const std::string & pName, int index)
{
	assert(ProgramId);
	glBindAttribLocation(ProgramId, index, pName.c_str());
}

void ShaderProgram::addUniform(const std::string & uName)
{
	assert(ProgramId);
	GLint loc = glGetUniformLocation(ProgramId, uName.c_str());
	uniforms.insert(std::pair<std::string, GLint>(uName, loc));
}

void ShaderProgram::addUniformBlock(const std::string & bName, int location)
{
	assert(ProgramId);
	int UboId = glGetUniformBlockIndex(ProgramId, bName.c_str());
	glUniformBlockBinding(ProgramId, UboId, location);
}

GLint ShaderProgram::getUniform(const std::string & uName)
{
	return uniforms.find(uName)->second;
}

void ShaderProgram::BeginShader() {
	glUseProgram(ProgramId);
}

void ShaderProgram::EndShader() {
	glUseProgram(0);
}

void ShaderProgram::destroy()
{
	glUseProgram(0);
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

const std::string ShaderProgram::read(const std::string & filename)
{
	std::ifstream ifile(filename);
	std::string shader_string;
	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		shader_string += line + "\n";
	}
	return shader_string;
}

const GLuint ShaderProgram::checkCompilation(const GLuint shader_id, const std::string & filename)
{
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetShaderInfoLog(shader_id, length, &length, log);
		std::cerr << "[" << filename << "] " << std::endl << log;
		delete log;
	}
	return compiled;
}

void ShaderProgram::checkLinkage(const GLuint program_id)
{
	GLint linked;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		GLint length;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetProgramInfoLog(program_id, length, &length, log);
		std::cerr << "[LINK] " << std::endl << log << std::endl;
		delete log;
	}
}
