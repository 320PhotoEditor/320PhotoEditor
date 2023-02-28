#pragma once
#include "Common.h"

class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}
	
	sf::Texture* getTexture(std::string name);

private:
	AssetManager() {};

	std::map<std::string, sf::Texture*> textures;
};

