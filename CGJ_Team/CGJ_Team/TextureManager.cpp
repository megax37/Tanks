#include "TextureManager.h"

TextureManager* TextureManager::m_instance;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager * TextureManager::instance()
{
	if (!m_instance) {
		m_instance = new TextureManager();
	}
	return m_instance;
}

void TextureManager::add(const std::string& name, Texture * tex)
{
	// Store in map
	textures.insert(std::pair<std::string, Texture*>(name, tex));
}

Texture * TextureManager::get(const std::string& name)
{
	return textures.find(name)->second;
}

void TextureManager::destroy()
{
	textures.clear();
}
