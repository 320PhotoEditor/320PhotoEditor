#pragma once

#include "../Common.h"

//basically in image that we edit
//dont create directly
class Layer
{
public:

	Layer(sf::Vector2u size, sf::Color color);

	sf::Image* getImage();

	sf::Sprite* getSprite();

	~Layer();

private:

	sf::Texture texture;
	sf::Sprite* sprite;

	sf::Image* image;

	bool visible;
};

