#include "Texture.h"

Texture::Texture(const std::string & filename)
{
	load(filename);
	if (data == NULL) std::cout << "Não tem nada" << std::endl;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int textureType = GL_RGB;
	if (channels == 4)	textureType = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, textureType, width, height, 0, textureType, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	free(data);
}

Texture::~Texture()
{
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureID()
{
	return id;
}

void Texture::loadToShader(ShaderProgram * shader)
{
	glActiveTexture(GL_TEXTURE0);
	this->bind();
	GLint TexMode_UId = shader->getUniform("TexMode");
	glUniform1i(TexMode_UId, 1);
	GLint Tex_UId = shader->getUniform("Texmap");
	glUniform1i(Tex_UId, 0);
}

void Texture::unloadFromShader(ShaderProgram * shader)
{
	this->unbind();
	GLint TexMode_UId = shader->getUniform("TexMode");
	glUniform1i(TexMode_UId, 0);
}

void Texture::load(const std::string & filename)
{
	data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
}
