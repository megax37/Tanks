#ifndef _TEXTURE_
#define _TEXTURE_

#include "engine.h"

class Texture
{
public:

	Texture(const std::string& filename);
	~Texture();

	void bind();
	void unbind();

	GLuint getTextureID();

private:

	GLuint id;
	int channels;
	int width;
	int height;
	unsigned char *data;

	void load(const std::string& filename);
};

#endif