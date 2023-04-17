#include "AssetManager.h"

sf::Texture* AssetManager::getTexture(std::string name)
{
	auto search = textures.find(name);
	if(search != textures.end())
	{
		return search->second;
	}
	else
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(name);
		textures.insert(std::make_pair(name, texture));
		return texture;
	}
}

ComputeShader* AssetManager::getComputeShader(std::string name)
{
	auto search = computeShaders.find(name);
	if (search != computeShaders.end())
	{
		return search->second;
	}
	else
	{
		ComputeShader* computeShader = new ComputeShader(name.c_str());
		computeShaders.insert(std::make_pair(name, computeShader));
		return computeShader;
	}
}
