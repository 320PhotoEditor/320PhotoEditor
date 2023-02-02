#pragma once

#include "../Common.h"

class Layer
{
public:

	Layer(sf::Vector2u size, sf::Color color);

	sf::Image* getImage();

private:

	sf::Image* image;

	bool visible;
};

