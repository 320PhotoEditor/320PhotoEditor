#include "Layer.h"

Layer::Layer(sf::Vector2u size, sf::Color color)
{
	image = new sf::Image();
	image->create(size.x, size.y, color);

	texture = sf::Texture();
	texture.loadFromImage(*image);

	sprite = new sf::Sprite(texture);

	visible = true;
}

sf::Image* Layer::getImage()
{
	return image;
}

sf::Sprite* Layer::getSprite()
{
	return sprite;
}

Layer::~Layer()
{
	delete sprite;
	delete image;
}