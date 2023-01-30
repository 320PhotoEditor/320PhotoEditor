#include "Layer.h"

Layer::Layer(sf::Vector2u size, sf::Color color)
{
	image = new sf::Image();
	image->create(size.x, size.y, color);

	visible = true;
}

sf::Image* Layer::getImage()
{
	return image;
}
