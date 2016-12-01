#ifndef _TEXTURE_MANAGER_
#define _TEXTURE_MANAGER_

#include "Texture.h"

class TextureManager {

public:
	static TextureManager* instance();
	void add(const std::string& name, Texture* tex);
	Texture* get(const std::string& name);

	void destroy();

private:
	static TextureManager* m_instance;

	std::map<std::string, Texture*> textures;

	TextureManager();
	~TextureManager();
};

#endif
